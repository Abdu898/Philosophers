/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahin <ashahin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:49:47 by ashahin           #+#    #+#             */
/*   Updated: 2023/05/12 21:29:38 by ashahin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//which philo died
void	ft_check_died(t_args *args)
{
	int	i;

	i = -1;
	while (!(args->all_ate))
	{
		i = -1;
		while (++i < args->n_philo && !(args->died))
		{
			pthread_mutex_lock(&(args->writing));
			if (ft_get_time_ms() - args->philo[i].t_last_meal > args->t_die)
			{
				ft_print_action(args, "died");
				args->died = 1;
			}
			pthread_mutex_unlock(&(args->writing));
			usleep(100);// delay * 2!
		}
		//function to check which died
		if (args->died)
			break ;
		i = 0;
		while (args->n_eat != -1 && i < args->n_philo
			&& args->philo[i].x_ate >= args->n_eat)
			i++;
		if (i == args->n_philo)
			args->all_ate = 1;
	}
}

void	ft_philo_eats(t_args *args)
{
	pthread_mutex_lock(&(args->forks[args->philo[args->p_i].l_fork]));
	ft_print_action(args, "has taken a fork");
	pthread_mutex_lock(&(args->forks[args->philo[args->p_i].r_fork]));
	ft_print_action(args, "has taken a fork");
	pthread_mutex_lock(&(args->meal_check));
	ft_print_action(args, "is eating");
	args->philo[args->p_i].t_last_meal = ft_get_time_ms() - args->t_start;
	pthread_mutex_unlock(&(args->meal_check));
	ft_smart_sleep(args, args->t_eat);
	(args->philo[args->p_i].x_ate)++;
	pthread_mutex_unlock(&(args->forks[args->philo[args->p_i].l_fork]));
	pthread_mutex_unlock(&(args->forks[args->philo[args->p_i].r_fork]));
}

void	*ft_philo_routine(void *void_args)
{
	t_args	*args;

	args = (t_args *)void_args;
	if ((args->p_i) % 2 != 0)
		usleep(50);
	// ft_philo_eats(args);
	while (!(args->died))
	{
		ft_philo_eats(args);
		if (args->all_ate)
			break ;
		ft_print_action(args, "is_sleeping");
		ft_smart_sleep(args, args->t_sleep);
		ft_print_action(args, "is thinking");
	}
	return (NULL);
}
