/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahin <ashahin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 22:47:35 by ashahin           #+#    #+#             */
/*   Updated: 2023/05/06 21:37:43 by ashahin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
			sign = -1;
		i++;
	}
	while (strn[i] != '\0' && (strn[i] >= '0' && strn[i] <= '9'))
		res = res * 10 + (strn[i++] - '0');
	return (res * sign);
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	ft_destroy_forks(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->n_philo)
	{
		if (pthread_mutex_destroy(&args->forks[i]) != 0)
			ft_putstr_fd("Error: Failed destroying mutex for fork\n", 2);
	}
}

void	exit_with_error(char *errorMessage, t_args *args)
{
	if (args->philo)
		free(args->philo);
	if (args->forks)
		free(args->forks);
	ft_destroy_forks(args);
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(errorMessage, 2);
	ft_putstr_fd("\n", 2);
	exit(EXIT_FAILURE);
}

void	ft_init_args(int argc, char **argv, t_args *args)
{
	// args->philo = NULL;
	// args->forks = NULL;
	if (argc < 5 || argc > 6)
		exit_with_error("Usage: ./philo number_of_philosophers, time_to_die,"
			" time_to_eat, time_to_sleep,"
			" [number_of_times_each_philosopher_must_eat]", args);
	args->n_philo = ft_atoi(argv[1]);
	args->t_die = ft_atoi(argv[2]);
	args->t_eat = ft_atoi(argv[3]);
	args->t_sleep = ft_atoi(argv[4]);
	args->n_eat = -1;//
	if (argc == 6)
		args->n_eat = ft_atoi(argv[5]);
}
