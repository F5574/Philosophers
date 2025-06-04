/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routines_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:00:00 by gvon-ah-          #+#    #+#             */
/*   Updated: 2025/06/03 17:43:19 by gvon-ah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*life_routine_part2(t_philos *philo, pthread_mutex_t *fork_one,
		pthread_mutex_t *fork_two, unsigned int *cycle_count)
{
	if (!act("is eating\n", philo, philo->ctl->eat_t))
	{
		pthread_mutex_unlock(fork_two);
		pthread_mutex_unlock(fork_one);
		return (NULL);
	}
	meals_iteration(philo);
	pthread_mutex_unlock(fork_two);
	pthread_mutex_unlock(fork_one);
	if (!act("is sleeping\n", philo, philo->ctl->sleep_t))
		return (NULL);
	if (philo->ctl->die_t < 4 * philo->ctl->eat_t)
	{
		if (!safe_printf("is thinking\n", philo->ctl, philo))
			(*cycle_count)++;
		else
			return (NULL);
	}
	else if (!act("is thinking\n", philo, 0))
		return (NULL);
	return ((void *)1);
}

void	*life_routine(void *arg)
{
	t_philos		*philo;
	pthread_mutex_t	*fork_one;
	pthread_mutex_t	*fork_two;
	unsigned int	cycle_count;
	void			*ret;

	philo = (t_philos *)arg;
	initial_usleep(philo);
	cycle_count = 0;
	while (!is_dead(philo->ctl))
	{
		if (cycle_count > 0 && philo->ctl->die_t < 4 * philo->ctl->eat_t)
			usleep(philo->id * 2);
		if (!take_forks(philo))
			break ;
		choose_forks(philo, &fork_one, &fork_two);
		get_time_last_meal(philo);
		ret = life_routine_part2(philo, fork_one, fork_two, &cycle_count);
		if (ret == NULL)
			break ;
	}
	return (NULL);
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
		pthread_mutex_unlock(&ctl->life);
		pthread_mutex_lock(&ctl->print);
		printf("All philosophers have eaten at least %d times\n", ctl->meals_n);
		pthread_mutex_unlock(&ctl->print);
		return (1);
	}
	return (0);
}

void	error_pthread(t_ctl *ctl)
{
	printf("ERROR: Failed to create thread\n");
	pthread_mutex_lock(&ctl->life);
	ctl->termination = 1;
	pthread_mutex_unlock(&ctl->life);
}
