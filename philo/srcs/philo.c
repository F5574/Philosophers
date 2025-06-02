/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 20:35:03 by gvon-ah-          #+#    #+#             */
/*   Updated: 2025/06/02 19:23:24 by gvon-ah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_ctl	ctl;

	if (argc < 5 || argc > 6)
		return (print_str_fd(2, "Error: Invalid number of arguments\n"), 1);
	init_0_ctl(&ctl);
	if (check_input(argc, argv) == -1 || init_ctl(argc, argv, &ctl) == -1
		|| init_forks(&ctl) == -1 || init_monitor(&ctl) == -1)
	{
		free_ctl(&ctl);
		return (2);
	}
	ctl.philos = malloc(sizeof(t_philos) * ctl.philos_c);
	if (!ctl.philos)
	{
		free_ctl(&ctl);
		return (3);
	}
	create_philos(&ctl);
	if (init_threads(&ctl) == -1)
	{
		free_ctl(&ctl);
		return (4);
	}
	free_ctl(&ctl);
	return (0);
}