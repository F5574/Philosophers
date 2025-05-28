/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_inits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 20:05:14 by gvon-ah-          #+#    #+#             */
/*   Updated: 2025/05/28 22:00:01 by gvon-ah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_0_ctl(t_ctl *ctl)
{
	ctl->start_t = 0;
	ctl->philos_c = 0;
	ctl->die_t = 0;
	ctl->eat_t = 0;
	ctl->sleep_t = 0;
	ctl->think_t = 0;
	ctl->meals_n = 0;
	ctl->termination = 0;
	ctl->eaten_n = 0;
	ctl->philos = NULL;
	ctl->forks = NULL;
	ctl->monitor = 0;
	ctl->life_flag = 0;
	ctl->meals_flag = 0;
	ctl->print_flag = 0;
}

int	init_ctl(int argc, char *argv[], t_ctl *ctl)
{
	ctl->philos_c = ft_atoi(argv[1]);
	ctl->die_t = ft_atoi(argv[2]);
	ctl->eat_t = ft_atoi(argv[3]);
	ctl->sleep_t = ft_atoi(argv[4]);
	if (ctl->philos_c == 0 || ctl->die_t == 0
		|| ctl->eat_t == 0 || ctl->sleep_t == 0)
		return (-1);
	if (argc == 6)
	{
		ctl->meals_n = ft_atoi(argv[5]);
		if (ctl->meals_n == 0)
			return (-1);
	}
	if (ctl->philos_c == 1)
	{
		usleep(ctl->die_t * 1000);
		printf("0 1 was taken a fork\n%d 1 died\n", ctl->die_t);
		return (-1);
	}
	else
	ctl->think_t = get_time_think(ctl->philos_c,
		ctl->sleep_t, ctl->eat_t);
	return (0);
}

int init_forks(t_ctl *ctl)
{
	int	i;

	i = -1;
	ctl->forks = malloc(sizeof(pthread_mutex_t) * ctl->philos_c);
	if (!ctl->forks)
		return (print_str_fd(2, "ERROR: Failed creating forks\n"), -1);
	while ((int)ctl->philos_c > ++i)
	{
		if(pthread_mutex_init(&ctl->forks[i], NULL) != 0)
			return (print_str_fd(2, "ERROR: Failed creating forks\n"), -1);
	}
	return (0);
}

int	init_monitor(t_ctl *ctl)
{
	if (pthread_mutex_init(&ctl->life, NULL) != 0)
	{
		return (print_str_fd(2, "ERROR: Failed creating mutex(life)\n"), -1);;
	}
	ctl->life_flag = 1;
	if (pthread_mutex_init(&ctl->print, NULL) != 0)
	{
		return (print_str_fd(2, "ERROR: Failed creating mutex(print)\n"), -1);
	}
	ctl->print_flag = 1;
	if (pthread_mutex_init(&ctl->meals, NULL) != 0)
	{
		return (print_str_fd(2, "ERROR: Failed creating mutex(meals)\n"), -1);
	}
	ctl->meals_flag = 1;
	return (0);
}

void	create_philos(t_ctl *ctl)
{
	int	i;

	i = -1;
	while ((int)ctl->philos_c > ++i)
	{
		ctl->philos[i].id = i + 1;
		ctl->philos[i].meals_eaten = 0;
		ctl->philos[i].last_meal_t = 0;
		ctl->philos[i].ctl = ctl;
		ctl->philos[i].thread_id = 0;
		ctl->philos[i].my_fork = &ctl->forks[i];
	}
}