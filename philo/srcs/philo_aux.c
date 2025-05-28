/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 19:00:51 by gvon-ah-          #+#    #+#             */
/*   Updated: 2025/05/28 22:08:58 by gvon-ah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_str_fd(int fd, char* str)
{
	while(*str)
		write(fd, str++, 1);
}

int	ft_atoi(const char *str)
{
	int	a;
	int	count;
	int	res;

	a = 0;
	res = 0;
	count = 1;
	while (str[a] == ' ' || (str[a] >= 9 && str[a] <= 13))
		a++;
	if (str[a] == '-' || str[a] == '+')
		if (str[a++] == '-')
			count *= -1;
	while (str[a] >= '0' && str[a] <= '9')
		res = res * 10 + (str[a++] - '0');
	return (count * res);
}

unsigned int ft_gettime(void)
{
	unsigned int	time;
	struct timeval	t_value;

	gettimeofday(&t_value, NULL);
	time = (t_value.tv_sec * 1000) + (t_value.tv_sec / 1000);
	return (time);
}

int check_input(int argc, char *argv[])
{
	int	i;
	int	x;

	i = 1;
	while (++i < argc)
	{
		x = 0;
		while (argv[i][x])
		{
			if (argv[i][x] < '0' || argv[i][x] > '9')
				return (print_str_fd(2, "Error: Only params with numbers!"), -1);
			else
				x++;
		}	
	}
	return (0);
}

int	exterminate(t_ctl *ctl)
{
	pthread_mutex_lock(&ctl->meals);
	if (ctl->eaten_n == ctl->philos_c)
	{
		ctl->termination = 1;
		pthread_mutex_unlock(&ctl->life);
		pthread_mutex_unlock(&ctl->meals);
		return (1);
	}
	pthread_mutex_unlock(&ctl->life);
	pthread_mutex_unlock(&ctl->meals);
	return (0);
}