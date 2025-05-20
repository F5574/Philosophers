/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_frees.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 19:25:36 by gvon-ah-          #+#    #+#             */
/*   Updated: 2025/05/20 20:03:45 by gvon-ah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_ctl(t_ctl *ctl)
{
	if (ctl->philos)
		free_philos(ctl);
	if (ctl->forks)
		free_forks(ctl);
	if (ctl->life_flag)
		pthread_mutex_destroy(&ctl->life);
	if (ctl->print_flag)
		pthread_mutex_destroy(&ctl->print);
	if (ctl->meals_flag)
		pthread_mutex_destroy(&ctl->meals);
}

void	free_philos(t_ctl *ctl)
{
	int	i;

	i = -1;
	while (++i < ctl->philos_c)
	{
		ctl->philos[i].my_fork = NULL;
		ctl->philos[i].ctl = NULL;
	}
	free(ctl->philos);
}

void	free_forks(t_ctl *ctl)
{
	int	i;

	i = -1;
	while (++i < ctl->philos_c)
		pthread_mutex_destroy(&ctl->forks[i]);
	free(ctl->forks);
	ctl->forks = NULL;
}

void	is_dead(t_ctl *ctl, unsigned int *i)
{
	pthread_mutex_unlock(&ctl->life);
	printf("%lu %d died\n", ft_gettime() - ctl->start_t,
		ctl->philos[*i].id);
}

void	error_thread(t_ctl *ctl)
{
	printf("ERROR: Try to create a thread\n");
	pthread_mutex_lock(&ctl->life);
	ctl->termination = 1;
	pthread_mutex_unlock(&ctl->life);
}