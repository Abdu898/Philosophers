/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahin <ashahin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:51:05 by ashahin           #+#    #+#             */
/*   Updated: 2023/05/20 04:24:42 by ashahin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_exit_philo(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->n_philo)
		pthread_join(args->philo_thread[i], NULL);
	pthread_join(args->philo_thread[i], NULL);
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

void	ft_creat_threads(t_args *args)
{
	int	i;

	args->t_start = ft_get_time_ms();
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
