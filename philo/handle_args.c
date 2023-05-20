/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahin <ashahin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 22:47:35 by ashahin           #+#    #+#             */
/*   Updated: 2023/05/20 02:49:03 by ashahin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_philos_args(t_args	*args)
{
	int	i;

	i = -1;
	while (++i < args->n_philo)
	{
		args->philo[i].t_die = args->t_die;
		args->philo[i].t_eat = args->t_eat;
		args->philo[i].t_sleep = args->t_sleep;
		args->philo[i].n_eat = args->n_eat;
		args->philo[i].id = i + 1;
		args->philo[i].x_ate = 0;
		args->philo[i].t_start = 0;
		args->philo[i].t_last_meal = 0;
		args->philo[i].death_call_out = 0;
		args->philo[i].all_ate = 0;
	}
}

void	ft_check_args(t_args *args)
{
	if (args->n_philo < PHILO_MIN)
		exit_with_error(
			"The number of philosophers must be at least 2.", args, 0);
	if (args->n_philo > PHILO_MAX)
		exit_with_error(
			"The maximum number of philosophers allowed is 250.", args, 0);
	if (args->t_die < 0 || args->t_eat < 0 || args->t_sleep < 0)
		exit_with_error("time_to_die, time_to_eat and time_to_sleep"
			" must be <= 0.", args, 0);
}

void	ft_init_args(int argc, char **argv, t_args *args)
{
	if (argc < 5 || argc > 6)
		exit_with_error("Usage: ./philo number_of_philosophers, time_to_die,"
			" time_to_eat, time_to_sleep,"
			" [number_of_times_each_philosopher_must_eat]", args, 0);
	args->n_philo = ft_atoi(argv[1]);
	args->t_die = ft_atoi(argv[2]);
	args->t_eat = ft_atoi(argv[3]);
	args->t_sleep = ft_atoi(argv[4]);
	args->n_eat = -1;
	args->stop_prog = 0;
	if (argc == 6)
	{
		if (ft_atoi(argv[5]) <= 0)
			exit_with_error("number_of_times_each_philosopher_must_eat"
				" must be at least 1.", args, 0);
		args->n_eat = ft_atoi(argv[5]);
	}
	ft_check_args(args);
	ft_init_philos_args(args);
}
