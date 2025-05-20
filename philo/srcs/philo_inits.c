/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_inits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 20:05:14 by gvon-ah-          #+#    #+#             */
/*   Updated: 2025/05/20 20:09:57 by gvon-ah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_ctl(t_ctl *ctl)
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