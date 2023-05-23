/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahin <ashahin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:51:05 by ashahin           #+#    #+#             */
/*   Updated: 2023/05/21 02:06:35 by ashahin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_exit_philo(t_args *args)
{
	int	i;

	i = -1;
	if (args->n_philo > 1)
	{
		while (++i < args->n_philo)
			pthread_join(args->philo_thread[i], NULL);
		pthread_join(args->philo_thread[i], NULL);
	}
	i = -1;
	while (++i < args->n_philo)
	{
		if (pthread_mutex_destroy(&args->forks[i]) != 0)
			printf("Error: Failed destroying mutex for fork[%d]\n", i);
		if (pthread_mutex_destroy(&(args->philo[i].meal_check)) != 0)
			printf("Error: Failed destroying mutex for meal_check\n");
		if (pthread_mutex_destroy(&(args->philo[i].died_check)) != 0)
			printf("Error: Failed destroying mutex for died_check\n");
	}
	if (pthread_mutex_destroy(&(args->writing)) != 0)
		printf("Error: Failed destroying mutex for fork[%d]\n", i);
}

int	ft_one_philo_routine(t_args *args)
{
	args->philo[0].t_start = args->t_start;
	args->philo[0].t_last_meal = args->t_start;
	if (args->n_philo > 1)
		return (0);
	ft_print_action(&args->philo[0], "has taken a fork");
	ft_smart_sleep(&args->philo[0], args->t_start, args->t_die);
	ft_print_action(&args->philo[0], "died");
	return (1);
}

void	ft_creat_threads(t_args *args)
{
	int	i;

	args->t_start = ft_get_time_ms();
	if (ft_one_philo_routine(args))
		return ;
	if (args->t_die == 0)
	{
		printf("0 1 died\n");
		return ;
	}
	i = -1;
	while (++i < args->n_philo)
	{
		args->philo[i].t_start = args->t_start;
		args->philo[i].t_last_meal = args->t_start;
		if (pthread_create(&args->philo_thread[i], NULL,
				&ft_philo_routine, &(args->philo[i])) != 0)
			exit_with_error("Failed to create philosopher thread", args, 1);
	}
	if (pthread_create(&args->philo_thread[i], NULL,
			&ft_check_death, args) != 0)
		exit_with_error("Failed to create death_checker thread", args, 1);
}

int	main(int argc, char **argv)
{
	t_args	args;

	memset((void *)&args, 0, sizeof(t_args));
	ft_init_args(argc, argv, &args);
	ft_init_philos_forks(&args);
	ft_creat_threads(&args);
	ft_exit_philo(&args);
	return (0);
}
