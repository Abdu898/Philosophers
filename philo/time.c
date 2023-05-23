/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahin <ashahin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:50:47 by ashahin           #+#    #+#             */
/*   Updated: 2023/05/22 06:36:29 by ashahin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_t_think(t_philo *philo)
{
	long	t_think;

	t_think = 1;
	while (philo->t_die >= (2 * philo->t_eat + t_think * 3 + TIME_LOST)
		&& (t_think <= philo->t_eat && t_think <= philo->t_sleep)
		&& (t_think <= philo->t_die / 5)
		&& philo->t_eat >= philo->t_sleep)
		t_think++;
	while (philo->t_die
		>= (philo->t_eat + philo->t_sleep + t_think * 3 + TIME_LOST)
		&& (t_think <= philo->t_eat && t_think <= philo->t_sleep)
		&& (t_think <= philo->t_die / 5)
		&& philo->t_sleep > philo->t_eat)
		t_think++;
	if (philo->t_die < 50)
		while (philo->t_die > (philo->t_eat + philo->t_sleep + t_think) * 2)
			t_think += 1;
	if (philo->t_die <= 100 && philo->t_die >= 34
		&& philo->t_die >= (5 * philo->t_eat))
		while (philo->t_die > ((philo->t_eat * 10)
				+ philo->t_sleep + t_think))
			t_think += 1;
	if (t_think > 400)
		t_think = 200;
	return (t_think);
}

void	ft_t_lost(t_args *args)
{
	args->t_lost = TIME_LOST;
	if ((args->t_die < 100 && args->t_eat < 3 && args->t_sleep < 10)
		|| (args->t_die < 70 && args->t_eat < 7 && args->t_sleep < 15)
		|| (args->t_die < 50 && args->t_eat < 6 && args->t_sleep < 6)
		|| (args->t_die < 30 && args->t_eat < 11 && args->t_sleep < 11))
		args->t_lost = TIME_LOST * 10;
	if (args->t_die - (args->t_eat + args->t_sleep - 1) <= 0)
		args->t_lost = 0;
}

long	ft_get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long)(tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/*let the philo have the time needed to eat, sleep or think*/
void	ft_smart_sleep(t_philo *philo, long t_begin, long t_duration)
{
	while (ft_get_time_ms() - t_begin < t_duration)
	{
		usleep(BUFF_TIME * 10);
		if (!ft_should_continue(philo))
			return ;
	}
}
