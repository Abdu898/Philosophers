/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahin <ashahin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:50:57 by ashahin           #+#    #+#             */
/*   Updated: 2023/05/13 17:47:45 by ashahin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define PHILO_MAX 250
# define TIME_LOST 50
# define PHILO_MIN 2

# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>

// typedef struct s_args t_args;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				x_ate;
	long			t_start;
	long			t_last_meal;
	int				l_fork;
	int				r_fork;
	// t_args			*args;
}	t_philo;

typedef struct s_args
{
	int					n_philo;
	int					t_die;
	int					t_eat;
	int					t_sleep;
	int					n_eat;
	int					all_ate;
	int					died;
	int					dead_philo_id;
	pthread_mutex_t		*forks;
	t_philo				*philo;
	long				t_start;
	long				t_end;
	long				now;
	int					p_i;
	pthread_mutex_t		meal_check;
	pthread_mutex_t		writing;
}	t_args;
	// pthread_mutex_t		forks[PHILO_MAX];
	// t_philo				philo[PHILO_MAX];
//p_i; initialized in ft_creat_threads

//handle_args.c
void	ft_check_args(t_args *args);
void	ft_init_args(int argc, char **argv, t_args *args);

//utils.c
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nel, size_t elsize);
int		ft_atoi(const char *strn);
void	ft_putstr_fd(char *s, int fd);
void	ft_destroy_forks(t_args *args);
void	exit_with_error(char *errorMessage, t_args *args, int opt);
void	ft_print_action(t_args *args, char *str);

//philo
void	ft_creat_threads(t_args *args);
void	ft_create_philos_forks(t_args *args);
void	ft_exit_philo(t_args *args);

//routine.c
void	ft_check_died(t_args *args);
void	ft_philo_eats(t_args *args);
void	*ft_philo_routine(void *void_args);

//time.c
long	ft_get_time_ms(void);
long	ft_time_diff(long past, long now);
void	ft_smart_sleep(t_args *args, long t_time);//t_sleep

//dpug.c
void	dpug_args(t_args *args);
void	dpug_philo_mutex_vars(t_args *args);
void	dpug_all_philo_mutex_vars(t_args *args);

#endif