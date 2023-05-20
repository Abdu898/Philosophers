/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahin <ashahin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:50:47 by ashahin           #+#    #+#             */
/*   Updated: 2023/05/20 03:53:36 by ashahin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long)(tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long	ft_time_diff(long past, long now)
{
	return (now - past);
}

//let the philo eat the time to eat
void	ft_smart_sleep(t_philo *philo, long t_begin, long t_duration)
{
	while (ft_get_time_ms() - t_begin < t_duration)
	{
		usleep(TIME_LOST);
		if (!ft_should_continue(philo))
		{
			return ;
		}
	}
}
