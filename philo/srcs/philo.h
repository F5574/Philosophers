/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 20:17:45 by gvon-ah-          #+#    #+#             */
/*   Updated: 2025/05/28 21:49:47 by gvon-ah-         ###   ########.fr       */
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
}		t_philos;

/* Function prototypes */

// philo_aux.c
void			print_str_fd(int fd, char* str);
int				ft_atoi(const char *str);
unsigned int	ft_gettime(void);
int 			check_input(int argc, char *argv[]);
int				exterminate(t_ctl *ctl);

// philo_aux_1.c
unsigned int	get_time_think(unsigned int philos_c, unsigned int sleep_t, unsigned int eat_t);
int				initial_usleep(t_philos *philo);
unsigned int	safe_printf(char *msg, t_ctl *ctl, t_philos *philo);
void			choose_forks(t_philos *philo, pthread_mutex_t **fork_one, pthread_mutex_t **fork_two);
unsigned int	ft_my_time(void);

// philo_inits.c
void			init_0_ctl(t_ctl *ctl);
int				init_ctl(int argc, char *argv[], t_ctl *ctl);
int				init_forks(t_ctl *ctl);
int				init_monitor(t_ctl *ctl);
void			create_philos(t_ctl *ctl);

// philo_routines.c
int				act(char *msg, t_philos *philo, unsigned int time);
int				is_dead(t_ctl *ctl);
int				take_forks(t_philos *philo);
void			meals_iteration(t_philos *philo);
void			get_time_last_meal(t_philos *philo);

// philo_routines_1.c
int				threads_union(t_ctl *ctl);
int				init_threads(t_ctl *ctl);
void			*death_routine(void *arg);
void			*life_routine(void *arg);
int				extreminate_if(t_ctl *ctl);
void			error_pthread(t_ctl *ctl);

// philo_frees.c
void			free_ctl(t_ctl *ctl);
void			free_philos(t_ctl *ctl);
void			free_forks(t_ctl *ctl);
void			dead_msg(t_ctl *ctl, unsigned int *i);
void			error_thread(t_ctl *ctl);

// philo.c
int				main(int argc, char *argv[]);

#endif