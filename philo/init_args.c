/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahin <ashahin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 22:47:35 by ashahin           #+#    #+#             */
/*   Updated: 2023/05/23 02:01:30 by ashahin          ###   ########.fr       */
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
		args->philo[i].t_think = 0;
		args->philo[i].t_last_meal = 0;
		args->philo[i].death_call_out = 0;
		args->philo[i].all_ate = 0;
		args->philo[i].t_think = ft_t_think(&args->philo[i]);
	}
}

void	ft_check_args(int argc, char **argv, t_args *args)
{
	if (argc == 6)
	{
		if (ft_atoi(argv[5]) <= 0)
			exit_with_error("number_of_times_each_philosopher_must_eat"
				" must be at least 1.", args, 0);
		args->n_eat = ft_atoi(argv[5]);
	}
	if (args->n_philo > PHILO_MAX - 50)
		exit_with_error(
			"The maximum number of philosophers allowed is 200.", args, 0);
	if (args->t_die < 0 || args->t_eat < 0 || args->t_sleep < 0)
		exit_with_error("time_to_die, time_to_eat and time_to_sleep"
			" must be <= 0.", args, 0);
}

void	ft_handle_args(int argc, char **argv)
{
	int		i;
	char	*arg;

	i = 0;
	while (++i < argc)
	{
		arg = argv[i];
		while (*arg)
		{
			if ((*arg < '0' || *arg > '9') && *arg != '+')
			{
				if (*arg == '-')
					printf("Error: Arguments can't be negative numbers.\n");
				else
					printf("Error: Argument '%s'"
						" contains non-digit character.\n", argv[i]);
				exit(EXIT_FAILURE);
			}
			arg++;
		}
	}
}

void	ft_hadle_plus(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
		{
			if ((argv[i][j]) == '-' || argv[i][j] == '+')
			{
				if ((argv[i][j + 1]) < '0' || argv[i][j + 1] >= '9')
				{
					printf("please only POSITIVE"
						" NUMBERS without playing around!\n");
					exit(EXIT_FAILURE);
				}
			}
		}
	}
}

void	ft_init_args(int argc, char **argv, t_args *args)
{
	if (argc < 5 || argc > 6)
		exit_with_error("Usage: ./philo number_of_philosophers, time_to_die,"
			" time_to_eat, time_to_sleep,"
			" [number_of_times_each_philosopher_must_eat]", args, 0);
	ft_handle_args(argc, argv);
	ft_hadle_plus(argv);
	args->n_philo = ft_atoi(argv[1]);
	args->t_die = ft_atoi(argv[2]);
	args->t_eat = ft_atoi(argv[3]);
	args->t_sleep = ft_atoi(argv[4]);
	args->n_eat = -1;
	if (args->n_philo == 0)
		exit_with_error(" number of Philosophers should be a positive Number"
			" (more that Zero!)", args, 0);
	ft_check_args(argc, argv, args);
	ft_t_lost(args);
	ft_init_philos_args(args);
}
