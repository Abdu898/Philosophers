
#ifndef PHILO_H
# define PHILO_H

# define PHILO_MAX 250
# define TIME_LOST 50
# define PHILO_MIN 2

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				x_ate;
	long			t_start;
	long			t_last_meal;
	int				l_fork;
	int				r_fork;
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
	pthread_mutex_t		forks[PHILO_MAX];
	t_philo				philo[PHILO_MAX];
	long				t_start;
	long				t_end;
	long				now;
	pthread_mutex_t		meal_check;
	pthread_mutex_t		writing;
}	t_args;

//handle_args.c
void	ft_check_args(t_args *args);
void	ft_init_args(int argc, char **argv, t_args *args);

//utils.c
int		ft_atoi(const char *strn);
void	ft_putstr_fd(char *s, int fd);
void	ft_destroy_forks(t_args *args);
void	exit_with_error(char *errorMessage, t_args *args, int opt);
void	ft_print_action(t_args *args, int i, char *str);

//philo
void	ft_creat_threads(t_args *args);
void	ft_create_philos_forks(t_args *args);

//routine.c
void	ft_exit_philo(t_args *args);
void	ft_check_died(t_args *args);
void	ft_philo_eats(t_args *args, int i);
void	*ft_philo_routine(void *void_args);

//time.c
long	ft_get_time_ms(void);
long	ft_time_diff(long past, long now);
void	ft_smart_sleep(t_args *args, int i, long time);//t_sleep

#endif

#include "philo.h"

void	ft_check_args(t_args *args)
{
	if (args->n_philo < PHILO_MIN)
		exit_with_error(
			"The number of philosophers must be at least 2.", args, 0);
	if (args->n_philo > PHILO_MAX)
		exit_with_error(
			"The maximum number of philosophers allowed is 250.", args, 0);
	if (args->n_eat < 1)
		exit_with_error("number_of_times_each_philosopher_must_eat"
			" must be at least 1.", args, 0);
	if (args->t_die < 0 || args->t_eat < 0 || args->t_sleep < 0)
		exit_with_error("time_to_die, time_to_eat and time_to_sleep"
			" must be <= 0.", args, 0);
}

void	ft_init_args(int argc, char **argv, t_args *args)
{
	if (argc < 5 || argc > 6)
		exit_with_error("Usage: ./philo number_of_philosophers, time_to_die,"
			" time_to_eat, time_to_sleep,"
			" [number_of_times_each_philosopher_must_eat]", args, 0);
	args->n_philo = ft_atoi(argv[1]);
	args->t_die = ft_atoi(argv[2]);
	args->t_eat = ft_atoi(argv[3]);
	args->t_sleep = ft_atoi(argv[4]);
	args->n_eat = -1;
	if (argc == 6)
		args->n_eat = ft_atoi(argv[5]);
	ft_check_args(args);
}

long	ft_get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long)(tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long	ft_time_deff(long past, long now)
{
	return (now - past);
}

void	ft_smart_sleep(t_args *args, int i, long time)
{
	long	t;

	t = ft_get_time_ms();
	while (!(args->died))
	{
		if (ft_time_diff(t, ft_get_time_ms()) >= time)
			break ;
		usleep(TIME_LOST);
	}
}

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

void	exit_with_error(char *errorMessage, t_args *args, int opt)
{
	if (opt == 1)
	{
		if (args->philo)
			free(args->philo);
		if (args->forks)
			free(args->forks);
		ft_destroy_forks(args);
	}
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(errorMessage, 2);
	ft_putstr_fd("\n", 2);
	exit(EXIT_FAILURE);
}

/*change to print the l/r fork*/
void	ft_print_action(t_args *args, int i, char *str)
{
	pthread_mutex_lock(&(args->writing));
	if (!(args->died))
		printf("%li %i %s\n",
			ft_get_time_ms() - args->philo[i].t_start, args->philo[i].id, str);
	pthread_mutex_unlock(&(args->writing));
}


void	ft_exit_philo(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->all_ate)
		pthread_join(args->philo[i].thread, NULL);
	i = -1;
	while (++i < args->n_philo)
		pthread_mutex_destroy(&(args->forks[i]));
	pthread_mutex_destroy(&(args->writing));
	//pthread_mutex_destroy(&(args->meal_check));??????
}

void	ft_check_died2(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->n_philo && !(args->died))
	{
		pthread_mutex_lock(&(args->writing));
		if (ft_time_diff(args->philo[i].t_last_meal,
				ft_get_time_ms()) > args->t_die)
		{
			ft_print_action(args, i, "died");
			args->died = 1;
		}
		pthread_mutex_unlock(&(args->writing));
		usleep(100);// delay * 2!
	}
}

//which philo died
void	ft_check_died(t_args *args)
{
	int	i;

	i = -1;
	while (!(args->all_ate))
	{
		i = -1;
		while (++i < args->n_philo && !(args->died))
		{
			pthread_mutex_lock(&(args->writing));
			if (ft_time_diff(args->philo[i].t_last_meal,
					ft_get_time_ms()) > args->t_die)
			{
				ft_print_action(args, i, "died");
				args->died = 1;
			}
			pthread_mutex_unlock(&(args->writing));
			usleep(100);// delay * 2!
		}
		//function to check which died
		if (args->died)
			break ;
		i = 0;
		while (args->n_eat != -1 && i < args->n_philo
			&& args->philo[i].x_ate >= args->n_eat)
			i++;
		if (i == args->n_philo)
			args->all_ate = 1;
	}
}

void	ft_check_died(t_args *args)
{
	int	i;

	i = -1;
	while (!(args->all_ate))
	{
		i = -1;
		while (++i < args->n_philo && !(args->died))
		{
			pthread_mutex_lock(&(args->writing));
			if (ft_time_diff(args->philo[i].t_last_meal,
					ft_get_time_ms()) > args->t_die)
			{
				ft_print_action(args, i, "died");
				args->died = 1;
				args->dead_philo_id = args->philo[i].id;
			}
			pthread_mutex_unlock(&(args->writing));
			usleep(100);// delay * 2!
		}
		if (args->died)
		{
			printf("%li %i died\n",
				ft_get_time_ms() - args->philo[i].t_start, args->philo[i].id);
			return ;
		}
		i = 0;
		while (args->n_eat != -1 && i < args->n_philo
			&& args->philo[i].x_ate >= args->n_eat)
			i++;
		if (i == args->n_philo)
			args->all_ate = 1;
	}
}

void	ft_philo_eats(t_args *args, int i)
{
	pthread_mutex_lock(&(args->forks[args->philo[i].l_fork]));
	//change to print the l/r fork
	ft_print_action(args, i, "has taken a fork");
	pthread_mutex_lock(&(args->forks[args->philo[i].r_fork]));
	//change to print the l/r fork
	ft_print_action(args, i, "has taken a fork");
	pthread_mutex_lock(&(args->meal_check));
	ft_print_action(args, i, "is eating");
	args->philo[i].t_last_meal = ft_get_time_ms();
	pthread_mutex_unlock(&(args->meal_check));
	ft_smart_sleep(args, i, args->t_eat);
	(args->philo[i].x_ate);
	pthread_mutex_unlock(&(args->forks[args->philo[i].l_fork]));
	pthread_mutex_unlock(&(args->forks[args->philo[i].r_fork]));
}

void	*ft_philo_routine(void *void_args)
{
	int		i;
	t_args	*args;

	args = (t_args *)void_args;
	i = -1;
	//?????
	//if (args->philo[i].id > 2)
		// usleep(15000);
	while (!(args->died))
	{
		ft_philo_eats(args, i);
		if (args->all_ate)
			break ;
		ft_print_action(args, i, "is_sleeping");
		ft_smart_sleep(args, i, args->t_sleep);
		ft_print_action(args, i, "is thinking");
		return (NULL);
	}
}


void	ft_creat_threads(t_args *args)
{
	int			i;

	i = -1;
	while (++i < args->n_philo)
	{
		args->philo[i].t_start = args->t_start;
		args->philo[i].t_last_meal = args->t_start;
		if (pthread_create(&args->philo[i].thread, NULL,
				ft_philo_routine, args) != 0)
			exit_with_error("Failed to create philosopher thread", args, 1);
		args->philo[i].t_last_meal = ft_get_time_ms();
	}
	ft_check_dead(args);
	ft_exit_philo(args);
}

void	ft_create_philos_forks(t_args *args)
{
	int	i;

// init philos and mutex
	i = -1;
	while (++i < args->n_philo)
	{
		if (pthread_mutex_init(&args->forks[i], NULL) != 0)
			exit_with_error("Failed initializing mutex for fork", args, 1);
		args->philo[i].id = i + 1;
		args->philo[i].l_fork = i;
		args->philo[i].r_fork = (i + 1) % args->n_philo;
	}
	if (pthread_mutex_init(&args->writing, NULL) != 0)
		exit_with_error("Failed initializing mutex for Writing", args, 1);
	if (pthread_mutex_init(&args->meal_check, NULL) != 0)
		exit_with_error("Failed initializing mutex for meal_check", args, 1);
}

int	main(int argc, char **argv)
{
	t_args		args;

	ft_init_args(argc, argv, &args);
	ft_create_philos_forks(&args);
	args.t_start = ft_get_time_ms();
	ft_creat_threads(&args);
	return (0);
}
