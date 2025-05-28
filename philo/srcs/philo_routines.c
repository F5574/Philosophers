/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 20:57:33 by gvon-ah-          #+#    #+#             */
/*   Updated: 2025/05/28 21:04:24 by gvon-ah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	act(char *msg, t_philos *philo, unsigned int time)
{
	unsigned int	elapsed_time;
	unsigned int	interval;

	elapsed_time = 0;
	interval = 10;
	if (is_dead(philo->ctl))
		return (0);
	if (safe_printf(msg, philo->ctl, philo))
		return (0);
	while (elapsed_time < time)
	{
		usleep(interval * 1000);
		elapsed_time += interval;
		if (is_dead(philo->ctl))
			return (0);
	}
	return (1);
}

int	is_dead(t_ctl *ctl)
{
	pthread_mutex_lock(&ctl->life);
	if (ctl->termination)
	{
		pthread_mutex_unlock(&ctl->life);
		return (1);
	}
	pthread_mutex_unlock(&ctl->life);
	return (0);
}

int	take_forks(t_philos *philo)
{
	pthread_mutex_t	*fork_one;
	pthread_mutex_t	*fork_two;

	choose_forks(philo, &fork_one, &fork_two);
	if (philo->id % 2 == 0)
		usleep(100);
	pthread_mutex_lock(fork_one);
	if (safe_printf("has taken a fork\n", philo->ctl, philo))
	{
		pthread_mutex_unlock(fork_one);
		return (0);
	}
	pthread_mutex_lock(fork_two);
	if (safe_printf("has taken a fork\n", philo->ctl, philo))
	{
		pthread_mutex_unlock(fork_two);
		pthread_mutex_unlock(fork_one);
		return (0);
	}
	return (1);
}

void	meals_iteration(t_philos *philo)
{
	pthread_mutex_lock(&philo->ctl->meals);
	philo->meals_eaten++;
	if (philo->meals_eaten == philo->ctl->meals_n)
		philo->ctl->eaten_n++;
	pthread_mutex_unlock(&philo->ctl->meals);
}

void	get_time_last_meal(t_philos *philo)
{
	pthread_mutex_lock(&philo->ctl->life);
	philo->last_meal_t = ft_my_time();
	pthread_mutex_unlock(&philo->ctl->life);
}
