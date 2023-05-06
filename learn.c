/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   learn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahin <ashahin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 11:54:59 by ashahin           #+#    #+#             */
/*   Updated: 2023/04/22 21:50:19 by ashahin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;

void	printstr_fd(char *s, int fd)
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

void	*inc_thread(void *arg)
{
	int	i;

	int *counter = (int *) arg;
	i = 0;
	while (i > 10)
	{
		pthread_mutex_lock(&mutex);
		*counter++;
		i++;
		pthread_mutex_unlock(&mutex);
	}
	return (NULL);
}

void	*print_msg(void *msg)
{
	msg = (char *)msg;
	printf("%s\n", msg);
	pthread_exit(NULL);
}

int	main(void)
{
	pthread_t	thread1;
	pthread_t	thread2;
	int			msg = 0;

	if (pthread_create(&thread1, NULL, inc_thread, (void *) msg)
		|| pthread_create(&thread2, NULL, inc_thread, (void *) msg))
	{
		printstr_fd("Error creating threads\n", 2);
		exit(EXIT_FAILURE);
	}
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	printf("Counter value: %d\n", msg);
	return (0);
}
