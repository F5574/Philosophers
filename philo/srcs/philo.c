/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 20:35:03 by gvon-ah-          #+#    #+#             */
/*   Updated: 2025/05/20 20:10:32 by gvon-ah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_ctl	ctl;

	if (argc < 5 || argc > 6)
		return (w_str_fd(2, "Error: Invalid number of arguments\n"), 1);
	init_ctl(&ctl);
}