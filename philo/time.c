/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahin <ashahin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:50:47 by ashahin           #+#    #+#             */
/*   Updated: 2023/05/12 16:36:11 by ashahin          ###   ########.fr       */
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

void	ft_smart_sleep(t_args *args, long t_time)
{
	long	t;

	t = ft_get_time_ms();
	while (!(args->died))
	{
		if (ft_time_diff(t, ft_get_time_ms()) >= t_time)
			break ;
		usleep(TIME_LOST);
	}
}