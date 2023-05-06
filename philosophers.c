/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahin <ashahin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:51:05 by ashahin           #+#    #+#             */
/*   Updated: 2023/05/06 21:35:10 by ashahin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_philo_routine(t_args *args)
{
	
}

void	ft_init_forks(t_args *args)
{
	int	i;
// init mutex
	i = -1;
	while (++i < args->n_philo)
	{
		if (pthread_mutex_init(&args->forks[i], NULL) != 0)
			exit_with_error("Failed initializing mutex for fork", args);
		args->philo[i].left_fork = i;
		args->philo[i].right_fork = (i + 1) % args->n_philo;
	}
}

void	ft_creat_threads(t_args *args)
{
	int			i;

//init threads
	// args->philo = (t_philo *) malloc(args->n_philo * sizeof(t_philo));
	// if (!args->philo)
	// 	exit_with_error("Failed to allocate memory for philo struct", args);
	i = -1;
	while (++i < args->n_philo)
	{
		args->philo[i].id = i + 1;
		if (pthread_create(&args->philo[i].thread, NULL,
				ft_philo_routine, args) != 0)
			exit_with_error("Failed to create philosopher thread", args);
	}
}

int	main(int argc, char **argv)
{
	t_args		args;

	ft_init_args(argc, argv, &args);
	ft_init_forks(&args);
	ft_create_threads(&args);
	return (EXIT_SUCCESS);
}
