/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahin <ashahin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 00:19:53 by ashahin           #+#    #+#             */
/*   Updated: 2023/05/20 03:39:40 by ashahin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_philos_forks(t_args *args)
{
	int	i;

	if (pthread_mutex_init(&args->writing, NULL) != 0)
		exit_with_error("Failed initializing mutex for Writing", args, 1);
	i = -1;
	while (++i < args->n_philo)
	{
		if (pthread_mutex_init(&args->forks[i], NULL) != 0)
			exit_with_error("Failed initializing mutex for fork", args, 1);
		if (pthread_mutex_init(&args->philo[i].meal_check, NULL) != 0)
			exit_with_error("Failed"
				" initializing mutex for meal_check", args, 1);
		if (pthread_mutex_init(&args->philo[i].died_check, NULL) != 0)
			exit_with_error("Failed"
				" initializing mutex for died_check", args, 1);
		args->philo[i].l_fork = &(args->forks[i]);
		args->philo[i].r_fork = &(args->forks[(i + 1) % args->n_philo]);
		args->philo[i].writing = &(args->writing);
	}
}
