/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahin <ashahin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 01:49:25 by ashahin           #+#    #+#             */
/*   Updated: 2023/05/22 06:30:14 by ashahin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_are_all_full(t_args *args)
{
	int	i;
	int	nb_eaten;

	if (args->n_eat == -1)
		return (0);
	nb_eaten = 0;
	i = -1;
	while (++i < args->n_philo)
	{
		pthread_mutex_lock(&args->philo[i].x_ate_check);
		if (args->philo[i].x_ate >= args->n_eat)
			nb_eaten++;
		pthread_mutex_unlock(&args->philo[i].x_ate_check);
	}
	if (nb_eaten == args->n_philo)
		return (1);
	return (0);
}

int	ft_tell_all_ate(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->n_philo)
	{
		pthread_mutex_lock(&args->philo[i].meal_check);
		args->philo[i].all_ate = 1;
		pthread_mutex_unlock(&args->philo[i].meal_check);
	}
	return (1);
}

void	ft_call_out_death(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->n_philo)
	{
		pthread_mutex_lock(&(args->philo[i].died_check));
		args->philo[i].death_call_out = 1;
		pthread_mutex_unlock(&(args->philo[i].died_check));
	}
}

int	ft_is_dead(t_args *args, long curr_time, long time_diff, int i)
{
	if (time_diff - TIME_LOST >= args->t_die)
	{
		ft_call_out_death(args);
		pthread_mutex_lock(&args->writing);
		printf("%li %i died\n", curr_time
			- (args->philo[i].t_start + args->t_lost), args->philo[i].id);
		pthread_mutex_unlock(&args->writing);
		return (1);
	}
	pthread_mutex_unlock(&args->philo[i].meal_check);
	return (0);
}

void	*ft_check_death(void *void_args)
{
	t_args	*args;
	int		i;
	long	curr_time;
	long	time_diff;

	args = (t_args *)void_args;
	while (1)
	{
		i = -1;
		curr_time = ft_get_time_ms();
		while (++i < args->n_philo)
		{
			pthread_mutex_lock(&(args->philo[i].meal_check));
			time_diff = curr_time - args->philo[i].t_last_meal;
			pthread_mutex_unlock(&(args->philo[i].meal_check));
			if (ft_is_dead(args, curr_time, time_diff, i))
				return (NULL);
		}
		if (ft_are_all_full(args))
			if (ft_tell_all_ate(args))
				return (NULL);
		usleep(BUFF_TIME);
	}
	return (NULL);
}
