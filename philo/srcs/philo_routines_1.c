/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routines_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 21:03:14 by gvon-ah-          #+#    #+#             */
/*   Updated: 2025/05/28 22:05:25 by gvon-ah-         ###   ########.fr       */
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
			error_pthread(ctl);
			j = 0;
			while (j++ < i)
				pthread_join(ctl->philos[j].thread_id, NULL);
			return (-1);
		}
	}
	if (pthread_create(&ctl->monitor, NULL, &death_routine, ctl) != 0)
		error_pthread(ctl);
	if (threads_union(ctl) == -1)
		return (-1);
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
		while (ctl->philos_c > i++)
		{
			if ((ctl->philos[i].last_meal_t) != 0 && (ft_my_time()
					- ctl->philos[i].last_meal_t) > ctl->die_t)
			{
				ctl->termination = 1;
				dead_msg(ctl, &i);
				return (NULL);
			}
		}
		if (extreminate_if(ctl))
			break;
		else
			usleep(500);
		pthread_mutex_unlock(&ctl->life);
	}
	return (NULL);
}

static void	aux_unlock(pthread_mutex_t	*fork_one, pthread_mutex_t	*fork_two)
{
	pthread_mutex_unlock(fork_two);
	pthread_mutex_unlock(fork_one);
}

void	*life_routine(void *arg)
{
	t_philos		*philo;
	pthread_mutex_t	*fork_one;
	pthread_mutex_t	*fork_two;

	philo = (t_philos *)arg;
	initial_usleep(philo);
	while (!is_dead(philo->ctl))
	{
		if (!take_forks(philo))
			break ;
		choose_forks(philo, &fork_one, &fork_two);
		get_time_last_meal(philo);
		if (!act("is eating\n", philo, philo->ctl->eat_t))
		{
			aux_unlock(fork_one, fork_two);
			break ;
		}
		meals_iteration(philo);
		aux_unlock(fork_one, fork_two);
		if (!act("is sleeping\n", philo, philo->ctl->sleep_t) || 
			!act("is thinking\n", philo, 0))
			break ;
	}
	return (NULL);
}

void	error_pthread(t_ctl *ctl)
{
	printf("ERROR: Failed to create thread\n");
	pthread_mutex_lock(&ctl->life);
	ctl->termination = 1;
	pthread_mutex_unlock(&ctl->life);
}

int	extreminate_if(t_ctl *ctl)
{
	unsigned int	i;
	unsigned int	all_ate;

	i = 0;
	all_ate = 1;
	if (ctl->meals_n == 0)
		return (0);
	while (i < ctl->philos_c)
	{
		pthread_mutex_lock(&ctl->meals);
		if (ctl->philos[i].meals_eaten < ctl->meals_n)
			all_ate = 0;
		pthread_mutex_unlock(&ctl->meals);
		i++;
	}
	if (all_ate)
	{
		ctl->termination = 1;
		return (1);
	}
	return (0);
}
