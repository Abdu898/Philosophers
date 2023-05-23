/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahin <ashahin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:49:47 by ashahin           #+#    #+#             */
/*   Updated: 2023/05/22 06:19:30 by ashahin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_should_continue(t_philo *philo)
{
	pthread_mutex_lock(&philo->died_check);
	if (philo->death_call_out)
	{
		pthread_mutex_unlock(&philo->died_check);
		return (0);
	}
	pthread_mutex_unlock(&philo->died_check);
	pthread_mutex_lock(&philo->meal_check);
	if (philo->all_ate)
	{
		pthread_mutex_unlock(&philo->meal_check);
		return (0);
	}
	pthread_mutex_unlock(&philo->meal_check);
	return (1);
}

void	ft_philo_eats(t_philo *philo)
{
	long	curr_time;

	if (!ft_should_continue(philo))
		return ;
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(philo->r_fork);
	ft_print_action(philo, "has taken a fork");
	ft_print_action(philo, "has taken a fork");
	curr_time = ft_get_time_ms();
	if (!ft_should_continue(philo))
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	ft_print_action(philo, "is eating");
	pthread_mutex_lock(&philo->meal_check);
	philo->t_last_meal = curr_time;
	pthread_mutex_lock(&philo->x_ate_check);
	(philo->x_ate)++;
	pthread_mutex_unlock(&philo->x_ate_check);
	pthread_mutex_unlock(&philo->meal_check);
	ft_smart_sleep(philo, curr_time, philo->t_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	ft_philo_sleeps(t_philo *philo)
{
	if (!ft_should_continue(philo))
		return ;
	ft_print_action(philo, "is sleeping");
	ft_smart_sleep(philo, ft_get_time_ms(), philo->t_sleep);
}

void	ft_philo_thinks(t_philo *philo)
{
	long	curr_time;

	if (!ft_should_continue(philo))
		return ;
	ft_print_action(philo, "is thinking");
	curr_time = ft_get_time_ms();
	ft_smart_sleep(philo, curr_time, philo->t_think);
}

void	*ft_philo_routine(void *void_philo)
{
	t_philo	*philo;

	philo = (t_philo *)void_philo;
	while (1)
	{
		if (philo->id % 2 == 0)
			usleep(BUFF_TIME);
		usleep(BUFF_TIME * 3 / 2);
		if (philo->t_die < 33 || philo->t_eat < 5)
			usleep(BUFF_TIME * 5);
		ft_philo_eats(philo);
		ft_philo_sleeps(philo);
		ft_philo_thinks(philo);
		if (!ft_should_continue(philo))
			break ;
	}
	return (NULL);
}
