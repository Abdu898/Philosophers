/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahin <ashahin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:50:57 by ashahin           #+#    #+#             */
/*   Updated: 2023/05/23 01:59:21 by ashahin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define PHILO_MAX 250
# define TIME_LOST 1
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
	long			t_start;
	long			t_think;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*writing;
	pthread_mutex_t	meal_check;
	pthread_mutex_t	died_check;
	pthread_mutex_t	x_ate_check;
	int				death_call_out;
	int				x_ate;
	long			t_last_meal;
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
	long				t_lost;
	pthread_mutex_t		forks[PHILO_MAX];
	pthread_t			philo_thread[PHILO_MAX];
	t_philo				philo[PHILO_MAX];
	pthread_mutex_t		writing;
}	t_args;

//death_checker.c
int		ft_are_all_full(t_args *args);
int		ft_tell_all_ate(t_args *args);
void	ft_call_out_death(t_args *args);
int		ft_is_dead(t_args *args, long curr_time, long time_diff, int i);
void	*ft_check_death(void *void_args);

//init_args.c
void	ft_init_philo_args(t_args *args);
void	ft_check_args(int argc, char **argv, t_args *args);
void	ft_handle_args(int argc, char **argv);
void	ft_init_args(int argc, char **argv, t_args *args);
void	ft_hadle_plus(char **argv);

//init_forks.c
void	ft_init_philos_forks(t_args *args);

//philo
void	ft_exit_philo(t_args *args);
int		ft_one_philo_routine(t_args *args);
void	ft_creat_threads(t_args *args);
//main here

//routine.c
int		ft_should_continue(t_philo *philo);
void	ft_philo_eats(t_philo *philo);
void	ft_philo_sleeps(t_philo *philo);
void	ft_philo_thinks(t_philo *philo);
void	*ft_philo_routine(void *void_philo);

//time.c
long	ft_t_think(t_philo *philo);
void	ft_t_lost(t_args *args);
long	ft_get_time_ms(void);
void	ft_smart_sleep(t_philo *philo, long t_begin, long t_time);

//utils.c
int		ft_atoi(const char *strn);
void	ft_destroy_forks(t_args *args);
void	exit_with_error(char *errorMessage, t_args *args, int opt);
void	ft_print_action(t_philo *philo, char *str);

#endif