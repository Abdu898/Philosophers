/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dpug.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahin <ashahin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:38:58 by ashahin           #+#    #+#             */
/*   Updated: 2023/05/11 20:57:08 by ashahin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	dpug_args(t_args *args)
{
	printf("n_philo= %d\n", args->n_philo);
	printf("t_die= %d\n", args->t_die);
	printf("t_eat= %d\n", args->t_eat);
	printf("t_sleep= %d\n", args->t_sleep);
	printf("n_eat= %d\n", args->n_eat);
}

void	dpug_philo_mutex_vars(t_args *args)
{
	printf("philo[%d].id= %d\n", args->p_i, args->philo[args->p_i].id);
	printf("philo[%d].l_fork= %d\n", args->p_i, args->philo[args->p_i].l_fork);
	printf("philo[%d].r_fork= %d\n", args->p_i, args->philo[args->p_i].r_fork);
	printf("philo[%d].x_ate= %d\n", args->p_i, args->philo[args->p_i].x_ate);
	printf("philo[%d].t_start    = %ld\n",
		args->p_i, args->philo[args->p_i].t_start);
	printf("philo[%d].t_last_meal= %ld\n",
		args->p_i, args->philo[args->p_i].t_last_meal);
	printf("philo[%d].p_i= %d\n",args->p_i, args->p_i);
	printf("#######\n");
}

void	dpug_all_philo_mutex_vars(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->n_philo)
	{
		printf("philo[%d].id= %d\n", args->p_i, args->philo[args->p_i].id);
		printf("philo[%d].l_fork= %d\n", args->p_i, args->philo[args->p_i].l_fork);
		printf("philo[%d].r_fork= %d\n", args->p_i, args->philo[args->p_i].r_fork);
		printf("philo[%d].x_ate= %d\n", args->p_i, args->philo[args->p_i].x_ate);
		printf("philo[%d].t_start    = %ld\n", args->p_i, args->philo[args->p_i].t_start);
		printf("philo[%d].t_last_meal= %ld\n", args->p_i, args->philo[args->p_i].t_last_meal);
		printf("#######\n");
	}
}
