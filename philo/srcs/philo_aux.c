/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 19:00:51 by gvon-ah-          #+#    #+#             */
/*   Updated: 2025/06/03 18:14:17 by gvon-ah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_str_fd(int fd, char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		write(fd, &str[i], 1);
}

int	ft_atoi(const char *str)
{
	long	result;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result > (INT_MAX - (str[i] - '0')) / 10)
			return (-1);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return ((int)(result * sign));
}

unsigned int	ft_gettime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	check_input(int argc, char *argv[])
{
	int	i;
	int	j;
	int	value;

	i = 0;
	while (++i < argc)
	{
		j = -1;
		while (argv[i][++j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (print_str_fd(2,
						"ERROR: Arguments must be a integer\n"), -1);
		}
		if (j == 0 && argv[i][0] == '\0')
			return (print_str_fd(2,
					"ERROR: Arguments must not be empty\n"), -1);
		value = ft_atoi(argv[i]);
		if (value < 0)
			return (print_str_fd(2,
					"ERROR: Integer overflow in arguments\n"), -1);
	}
	return (0);
}

int	exterminate(t_ctl *ctl)
{
	pthread_mutex_lock(&ctl->life);
	ctl->termination = 1;
	pthread_mutex_unlock(&ctl->life);
	return (1);
}
