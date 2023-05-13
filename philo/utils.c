/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahin <ashahin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 01:35:52 by ashahin           #+#    #+#             */
/*   Updated: 2023/05/13 17:46:42 by ashahin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = -1;
	while (++i < n)
		((char *) s)[i] = '\0';
}

void	*ft_calloc(size_t nel, size_t elsize)
{
	void	*p;
	int		prod;

	p = malloc(nel * elsize);
	if (!p)
		return (NULL);
	prod = nel * elsize;
	ft_bzero(p, nel * elsize);
	return (p);
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
			printf("Error: Failed destroying mutex for fork\n");
			// ft_putstr_fd("Error: Failed destroying mutex for fork\n", 2);
	}
}

void	exit_with_error(char *errorMessage, t_args *args, int opt)
{
	if (opt == 1)
	{
		ft_destroy_forks(args);
	}
	printf("Error: %s \n", errorMessage);
	free(args);
	exit(EXIT_FAILURE);
}

/*change to print the l/r fork*/
void	ft_print_action(t_args *args, char *str)
{
	pthread_mutex_lock(&(args->writing));
	if (!(args->died))
		printf("%li %i %s\n",
			ft_get_time_ms() - args->philo[args->p_i].t_start,
			args->philo[args->p_i].id, str);
	pthread_mutex_unlock(&(args->writing));
}
