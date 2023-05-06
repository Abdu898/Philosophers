/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahin <ashahin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:50:57 by ashahin           #+#    #+#             */
/*   Updated: 2023/05/06 21:25:45 by ashahin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define PHILO_MAX 250
# define TIME_LOST 50

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				x_ate;
	long long		t_last_meal;
	int				left_fork;
	int				right_fork;
}	t_philo;

typedef struct s_args
{
	int					n_philo;
	int					t_die;
	int					t_eat;
	int					t_sleep;
	int					n_eat;
	pthread_mutex_t		forks[PHILO_MAX];
	t_philo				philo[PHILO_MAX];
	pthread_mutex_t		meal_check;
	pthread_mutex_t		writing;
}	t_args;

//handle_args.c
int		ft_atoi(const char *strn);
void	ft_putstr_fd(char *s, int fd);
void	ft_destroy_forks(t_args *args);
void	exit_with_error(char *errorMessage, t_args *args);
void	ft_init_args(int argc, char **argv, t_args *args);

//
void	ft_init_forks(t_args *args);
void	ft_creat_threads(t_args *args);
void	ft_philo_routine(t_args *args);

#endif