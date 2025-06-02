/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_aux_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:49:02 by gvon-ah-          #+#    #+#             */
/*   Updated: 2025/06/02 19:36:27 by gvon-ah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int	get_time_think(unsigned int philos_c,
	unsigned int sleep_t, unsigned int eat_t)
{
	if (philos_c % 2 == 0)
	{
		if (eat_t > sleep_t)
			return (eat_t - sleep_t);
		return (0);
	}
	else
	{
		if (eat_t * 2 > sleep_t)
			return (eat_t * 2 - sleep_t);
		return (0);
	}
}

int	initial_usleep(t_philos *philo)
{
	// Critical optimization for borderline timing cases (death_time ~3-4x eat_time)
	if (philo->ctl->die_t < 4 * philo->ctl->eat_t)
	{
		// For borderline cases, use a more aggressive staggering approach
		if (philo->id % 2 == 0)
		{
			// Even philosophers wait less to get their turn sooner
			usleep(philo->ctl->eat_t * 100); // Just 10% of eat_time
		}
		else if (philo->ctl->philos_c % 2 == 1 && philo->id == philo->ctl->philos_c)
		{
			// Last philosopher in odd-numbered group waits a bit more
			usleep(philo->ctl->eat_t * 150); // 15% of eat_time
		}
		return (1);
	}
	
	// Regular staggering for more relaxed timing constraints
	if (philo->id % 2 == 0)
	{
		usleep(philo->ctl->eat_t * 300); // 30% of eat_time
	}
	else if (philo->ctl->philos_c % 2 == 1 && philo->id == philo->ctl->philos_c)
	{
		usleep(philo->ctl->eat_t * 400); // 40% of eat_time
	}
	return (1);
}

unsigned int	safe_printf(char *msg, t_ctl *ctl, t_philos *philo)
{
	pthread_mutex_lock(&ctl->print);
	pthread_mutex_lock(&ctl->life);
	if (ctl->termination == 0)
	{
		printf("%lu %d %s", ft_my_time() - philo->ctl->start_t, philo->id, msg);
		pthread_mutex_unlock(&ctl->life);
		pthread_mutex_unlock(&ctl->print);
		return (0);
	}
	pthread_mutex_unlock(&ctl->life);
	pthread_mutex_unlock(&ctl->print);
	return (1);
}

void	choose_forks(t_philos *philo, pthread_mutex_t **fork_one,
	pthread_mutex_t **fork_two)
{
	unsigned int left_fork_idx;
	unsigned int right_fork_idx;

	left_fork_idx = philo->id - 1;
	if (philo->id == philo->ctl->philos_c)
		right_fork_idx = 0;
	else
		right_fork_idx = philo->id;

	if (&philo->ctl->forks[left_fork_idx] > &philo->ctl->forks[right_fork_idx])
	{
		*fork_one = &philo->ctl->forks[right_fork_idx];
		*fork_two = &philo->ctl->forks[left_fork_idx];
	}
	else
	{
		*fork_one = &philo->ctl->forks[left_fork_idx];
		*fork_two = &philo->ctl->forks[right_fork_idx];
	}
}

unsigned int	ft_my_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}