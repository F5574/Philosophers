/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routines_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 21:03:14 by gvon-ah-          #+#    #+#             */
/*   Updated: 2025/06/03 17:43:12 by gvon-ah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	threads_union(t_ctl *ctl)
{
	int	i;

	i = -1;
	while (++i < (int)ctl->philos_c)
	{
		if (pthread_join(ctl->philos[i].thread_id, NULL) != 0)
			return (-1);
	}
	if (pthread_join(ctl->monitor, NULL) != 0)
		return (-1);
	return (0);
}

int	init_threads(t_ctl *ctl)
{
	int	i;
	int	j;

	i = -1;
	ctl->start_t = ft_my_time();
	while (++i < (int)ctl->philos_c)
	{
		if (pthread_create(&ctl->philos[i].thread_id, NULL, &life_routine,
				&ctl->philos[i]) != 0)
		{
			j = 0;
			while (j++ < i)
				pthread_join(ctl->philos[j].thread_id, NULL);
			return (-1);
		}
	}
	if (pthread_create(&ctl->monitor, NULL, &death_routine, ctl) != 0)
	{
		return (-1);
	}
	return (0);
}

int	check_philosopher_status(t_ctl *ctl, unsigned int i)
{
	unsigned int	time_since_last_meal;

	if (ctl->philos[i].last_meal_t != 0)
	{
		time_since_last_meal = ft_my_time() - ctl->philos[i].last_meal_t;
		if (time_since_last_meal > ctl->die_t)
		{
			ctl->termination = 1;
			pthread_mutex_unlock(&ctl->life);
			dead_msg(ctl, &i);
			return (1);
		}
	}
	return (0);
}

void	*death_routine(void *arg)
{
	t_ctl			*ctl;
	unsigned int	i;

	ctl = (t_ctl *)arg;
	while (!ctl->termination)
	{
		i = 0;
		pthread_mutex_lock(&ctl->life);
		while (i < ctl->philos_c)
		{
			if (check_philosopher_status(ctl, i))
				return (NULL);
			i++;
		}
		if (extreminate_if(ctl))
			break ;
		pthread_mutex_unlock(&ctl->life);
		if (ctl->die_t > 1000)
			usleep(200);
		else if (ctl->die_t > 500)
			usleep(100);
		else
			usleep(50);
	}
	return (NULL);
}
