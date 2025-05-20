/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 20:17:45 by gvon-ah-          #+#    #+#             */
/*   Updated: 2025/05/20 20:02:56 by gvon-ah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <fcntl.h>
# include <pthread.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_philos	t_philos;

typedef struct s_ctl
{
	size_t			start_t;
	unsigned int	philos_c;
	unsigned int	die_t;
	unsigned int	eat_t;
	unsigned int	sleep_t;
	unsigned int	think_t;
	unsigned int	meals_n;
	unsigned int	eaten_n;
	unsigned int	termination;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	life;
	pthread_mutex_t	meals;
	pthread_t		monitor;
	t_philos		*philos;
	int				meals_flag;
	int				life_flag;
	int				print_flag;
	
}		t_ctl;

typedef struct s_philos
{
	unsigned int	id;
	pthread_t		thread_id;
	pthread_mutex_t	*my_fork;
	unsigned int	last_meal_t;
	unsigned int	meals_eaten;
	t_ctl			*ctl;
}		t_phios;

/* Function prototypes */

// philo_aux.c
void			print_str_fd(int fd, char* str);
int				ft_atoi(const char *str);
unsigned int	ft_gettime(void);
int 			check_input(int argc, char *argv[]);
int				exterminate(t_ctl *ctl);

// philo_frees.c
void			free_ctl(t_ctl *ctl);
void			free_philos(t_ctl *ctl);
void			free_forks(t_ctl *ctl);
void			is_dead(t_ctl *ctl, unsigned int *i);
void			error_thread(t_ctl *ctl);

// philo.c
int				main(int argc, char *argv[]);

#endif