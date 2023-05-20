/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahin <ashahin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:50:57 by ashahin           #+#    #+#             */
/*   Updated: 2023/05/20 04:28:12 by ashahin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define PHILO_MAX 250
# define TIME_LOST 100
# define BUFF_TIME 50
# define PHILO_MIN 2

# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <string.h>

typedef struct s_philo
{
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_eat;
	int				id;
	int				x_ate;
	long			t_start;
	long			t_last_meal;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*writing;
	pthread_mutex_t	meal_check;
	pthread_mutex_t	died_check;
	int				death_call_out;
	int				all_ate;
}	t_philo;

typedef struct s_args
{
	int					n_philo;
	int					t_die;
	int					t_eat;
	int					t_sleep;
	int					n_eat;
	long				t_start;
	int					all_ate;
	pthread_mutex_t		forks[PHILO_MAX];
	pthread_t			philo_thread[PHILO_MAX];
	t_philo				philo[PHILO_MAX];
	long				t_end;
	int					died;
	long				now;
	int					stop_prog;
	pthread_mutex_t		writing;
	pthread_mutex_t		sleep_mutex;
}	t_args;

//handle_args.c
void	ft_check_args(t_args *args);
void	ft_init_philo_args(t_args *args);
void	ft_init_args(int argc, char **argv, t_args *args);

//utils.c
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nel, size_t elsize);
int		ft_atoi(const char *strn);
void	ft_putstr_fd(char *s, int fd);
void	ft_destroy_forks(t_args *args);
void	exit_with_error(char *errorMessage, t_args *args, int opt);
void	ft_print_action(t_philo *philo, char *str);

//philo
void	ft_creat_threads(t_args *args);
void	ft_exit_philo(t_args *args);

//init_forks.c
void	ft_init_philos_forks(t_args *args);

//routine.c
int		ft_should_continue(t_philo *philo);
void	ft_philo_eats(t_philo *philo);
void	ft_philo_sleeps(t_philo *philo);
void	ft_philo_thinks(t_philo *philo);
void	*ft_philo_routine(void *void_philo);

//death_checker.c
int		ft_are_all_full(t_args *args);
void	ft_is_died(t_args *args);
void	ft_death_call_out(t_args *args);
void	*ft_check_death(void *void_args);

//time.c
long	ft_get_time_ms(void);
long	ft_time_diff(long past, long now);
void	ft_smart_sleep(t_philo *philo, long t_begin, long t_time);

//dpug.c
void	dpug_args(t_args *args);
void	dpug_philo_mutex_vars(t_args *args);
void	dpug_all_philo_mutex_vars(t_args *args);

#endif