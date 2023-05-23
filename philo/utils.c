/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahin <ashahin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 01:35:52 by ashahin           #+#    #+#             */
/*   Updated: 2023/05/23 01:59:09 by ashahin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *strn)
{
	int	res;
	int	i;
	int	sign;

	i = 0;
	while ((strn[i] >= 9 && strn[i] <= 13) || strn[i] == 32)
		i++;
	res = 0;
	sign = 1;
	if (strn[i] == '-' || strn[i] == '+')
	{
		if (strn[i] == '-')
		{
			sign = -1;
		}
		i++;
	}
	while (strn[i] != '\0' && (strn[i] >= '0' && strn[i] <= '9'))
		res = res * 10 + (strn[i++] - '0');
	return (res * sign);
}

void	ft_destroy_forks(t_args *args)
{
	int	i;

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

void	exit_with_error(char *errorMessage, t_args *args, int opt)
{
	if (opt == 1)
	{
		ft_destroy_forks(args);
	}
	printf("Error: %s \n", errorMessage);
	exit(EXIT_FAILURE);
}

void	ft_print_action(t_philo *philo, char *str)
{
	long	curr_time;

	curr_time = ft_get_time_ms();
	pthread_mutex_lock(philo->writing);
	if (!ft_should_continue(philo))
	{
		pthread_mutex_unlock(philo->writing);
		return ;
	}
	printf("%li %i %s\n", curr_time - philo->t_start, philo->id, str);
	pthread_mutex_unlock(philo->writing);
}
