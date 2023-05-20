/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahin <ashahin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 01:49:25 by ashahin           #+#    #+#             */
/*   Updated: 2023/05/20 04:23:56 by ashahin          ###   ########.fr       */
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
		if (args->philo[i].x_ate >= args->n_eat)
			nb_eaten++;
	if (nb_eaten == args->n_philo)
		return (1);
	return (0);
}

void	ft_is_dead(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->n_philo && !(args->died))
	{
		pthread_mutex_lock(&(args->writing));
		if (ft_get_time_ms() - args->philo[i].t_last_meal > args->t_die)
		{
			ft_print_action(args->philo + i, "died");
			args->died = 1;
		}
		pthread_mutex_unlock(&(args->writing));
		usleep(100);
	}
}

void	ft_tell_all_ate(t_args *args)
{
	int	i;

	i = -1;
	args->all_ate = 1;
	while (++i < args->n_philo)
		args->philo[i].all_ate = 1;
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

void	*ft_check_death(void *void_args)
{
	t_args	*args;
	int		i;
	long	curr_time;

	args = (t_args *)void_args;
	while (1)
	{
		//ft_is_died(args);
		i = -1;
		curr_time = ft_get_time_ms();
		while (++i < args->n_philo)
		{
			pthread_mutex_lock(&(args->philo[i].meal_check));
			if (curr_time - args->philo[i].t_last_meal > args->t_die)
			{
				pthread_mutex_unlock(&(args->philo[i].meal_check));
				ft_call_out_death(args);
				ft_print_action(&(args->philo[i]), "died");
				return (NULL);
			}
			pthread_mutex_unlock(&(args->philo[i].meal_check));
		}
		if (ft_are_all_full(args))
		{
			ft_tell_all_ate(args);
			return (NULL);
		}
	}
	return (NULL);
}
