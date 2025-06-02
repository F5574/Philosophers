/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_frees.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 19:25:36 by gvon-ah-          #+#    #+#             */
/*   Updated: 2025/06/02 19:29:45 by gvon-ah-         ###   ########.fr       */
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
	while (++i < (int)ctl->philos_c)
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
	while (++i < (int)ctl->philos_c)
		pthread_mutex_destroy(&ctl->forks[i]);
	free(ctl->forks);
	ctl->forks = NULL;
}

void	dead_msg(t_ctl *ctl, unsigned int *i)
{
	pthread_mutex_lock(&ctl->print);
	printf("%lu %d died\n", ft_my_time() - ctl->start_t,
		ctl->philos[*i].id);
	pthread_mutex_unlock(&ctl->print);
}

void	error_thread(t_ctl *ctl)
{
	printf("ERROR: Try to create a thread\n");
	pthread_mutex_lock(&ctl->life);
	ctl->termination = 1;
	pthread_mutex_unlock(&ctl->life);
}