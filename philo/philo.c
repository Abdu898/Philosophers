/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahin <ashahin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:51:05 by ashahin           #+#    #+#             */
/*   Updated: 2023/05/12 21:36:03 by ashahin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	ft_create_philos_forks(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->n_philo)
	{
		if (pthread_mutex_init(&args->forks[i], NULL) != 0)
			exit_with_error("Failed initializing mutex for fork", args, 1);
		args->philo[i].id = i + 1;
		args->philo[i].l_fork = i;
		args->philo[i].r_fork = (i + 1) % args->n_philo;
		args->philo[i].x_ate = 0;
	}
	if (pthread_mutex_init(&args->writing, NULL) != 0)
		exit_with_error("Failed initializing mutex for Writing", args, 1);
	if (pthread_mutex_init(&args->meal_check, NULL) != 0)
		exit_with_error("Failed initializing mutex for meal_check", args, 1);
}

void	ft_exit_philo(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->all_ate)
		pthread_join(args->philo[i].thread, NULL);
	i = -1;
	while (++i < args->n_philo)
		pthread_mutex_destroy(&(args->forks[i]));
	pthread_mutex_destroy(&(args->writing));
	pthread_mutex_destroy(&(args->meal_check));///////
	free(args);
}

void	ft_creat_threads(t_args *args)
{
	args->p_i = -1;
	args->t_start = ft_get_time_ms();
	while (++(args->p_i) < args->n_philo)
	{
		if (pthread_create(&args->philo[args->p_i].thread, NULL,
				&ft_philo_routine, args) != 0)
			exit_with_error("Failed to create philosopher thread", args, 1);
		args->philo[args->p_i].t_last_meal = ft_get_time_ms() - args->t_start;
	}
	// ft_check_died(args);
}

int	main(int argc, char **argv)
{
	t_args			*args;
	t_philo			*philo;
	pthread_mutex_t		*forks;

	args = (t_args *)malloc(sizeof(t_args *));
	if (!args)
	{
		printf("Error: allocating memory for args");
		return (1);
	}
	ft_init_args(argc, argv, args);
	ft_create_philos_forks(args);
	args->t_start = ft_get_time_ms();
	ft_creat_threads(args);
	ft_exit_philo(args);
	printf("######main#####\n");
	return (0);
}