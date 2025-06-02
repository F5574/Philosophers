/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routines_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 21:03:14 by gvon-ah-          #+#    #+#             */
/*   Updated: 2025/06/02 19:44:59 by gvon-ah-         ###   ########.fr       */
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
	{
		error_pthread(ctl);
		return (-1);
	}
	return (0);
}

void	*death_routine(void *arg)
{
	t_ctl			*ctl;
	unsigned int	i;
	unsigned int	time_since_last_meal;

	ctl = (t_ctl *)arg;
	while (!ctl->termination)
	{
		i = 0;
		pthread_mutex_lock(&ctl->life);
		while (i < ctl->philos_c)
		{
			if (ctl->philos[i].last_meal_t != 0)
			{
				time_since_last_meal = ft_my_time() - ctl->philos[i].last_meal_t;
				if (time_since_last_meal > ctl->die_t)
				{
					ctl->termination = 1;
					pthread_mutex_unlock(&ctl->life);
					dead_msg(ctl, &i);
					return (NULL);
				}
			}
			i++;
		}
		if (extreminate_if(ctl))
			break;
		pthread_mutex_unlock(&ctl->life);
		
		// Adaptive sleep based on die_time - uses less CPU when death time is large
		if (ctl->die_t > 1000)
			usleep(200);
		else if (ctl->die_t > 500)
			usleep(100);
		else
			usleep(50);
	}
	return (NULL);
}

void	*life_routine(void *arg)
{
	t_philos		*philo;
	pthread_mutex_t	*fork_one;
	pthread_mutex_t	*fork_two;
	unsigned int	cycle_count;

	philo = (t_philos *)arg;
	initial_usleep(philo);
	cycle_count = 0;
	while (!is_dead(philo->ctl))
	{
		// Special handling for tight timing cases after the first cycle
		if (cycle_count > 0 && philo->ctl->die_t < 4 * philo->ctl->eat_t)
		{
			// Add a very small wait between cycles for tightly timed scenarios
			// to break potential deadlocks
			usleep(philo->id * 2);
		}
		
		if (!take_forks(philo))
			break;
		choose_forks(philo, &fork_one, &fork_two);
		get_time_last_meal(philo);
		if (!act("is eating\n", philo, philo->ctl->eat_t))
		{
			pthread_mutex_unlock(fork_two);
			pthread_mutex_unlock(fork_one);
			break;
		}
		meals_iteration(philo);
		pthread_mutex_unlock(fork_two);
		pthread_mutex_unlock(fork_one);
		
		if (!act("is sleeping\n", philo, philo->ctl->sleep_t))
			break;
		
		// For borderline timing cases, make sure thinking doesn't take too long
		if (philo->ctl->die_t < 4 * philo->ctl->eat_t)
		{
			// Just announce thinking without any delay
			if (!safe_printf("is thinking\n", philo->ctl, philo))
				cycle_count++;
			else
				break;
		}
		else if (!act("is thinking\n", philo, 0))
			break;
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
		pthread_mutex_unlock(&ctl->life); // Release life mutex before printing
		pthread_mutex_lock(&ctl->print);
		printf("All philosophers have eaten at least %d times\n", ctl->meals_n);
		pthread_mutex_unlock(&ctl->print);
		return (1);
	}
	return (0);
}
