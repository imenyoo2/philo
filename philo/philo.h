/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 00:25:57 by ayait-el          #+#    #+#             */
/*   Updated: 2024/09/04 06:40:13 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct args
{
	int				number_of_philosophers;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	int				number_of_meals;
	int				has_died;
	struct timeval	*start;

	pthread_mutex_t	print_mutex;
	pthread_mutex_t	died;
	pthread_mutex_t	log_last_eat;
	pthread_mutex_t	start_simulation;
	pthread_mutex_t	log_num_of_meals;

	struct timeval	*last_eat_arr;
	int				*number_of_meals_arr;
	pthread_mutex_t	*mutex_arr;
}					t_args;

typedef struct philo_args
{
	t_args			*args;
	int				id;
}					t_philo_args;

t_args				*parse_argv(int argc, char **argv);
int					set_shared_data(t_args *args);
int					ft_atoi(const char *str);

/* threads */
void				free_mutex_arr(pthread_mutex_t *mutex_arr, int size);
pthread_mutex_t		*init_mutex_arr(int size);
void				*philosopher(t_philo_args *args);
int					run_threads(t_args *args);
int					run_and_monitor_threads(t_args *args,
						pthread_t *threads_arr);
int					spawn_threads(t_args *args, pthread_t *threads_arr);
t_philo_args		*alloc_philo_args(int id, t_args *args);
struct timeval		*alloc_last_eat_arr(int size);
int					*init_number_of_meals_arr(int size);
void				wait_for_threads(int size, pthread_t *threads_arr);

/* mutex */
int					mutex_lock(t_philo_args *args);
void				mutex_unlock(pthread_mutex_t *mutex_arr, int id, int n);

/* helpers */
long				calculate_timestamp(struct timeval *start,
						struct timeval *current);
void				timeval_copy(struct timeval *from, struct timeval *to);
int					update_current(struct timeval *current);
int					ft_usleep(long usec, t_args *args);
int					philo_has_died(struct timeval *last_eat,
						t_philo_args *args);
int					start_simulation(pthread_mutex_t *ready);
int					is_philo_full(t_philo_args *args);
int					has_died__(t_args *args);
void				set_has_died(t_args *args);
int					set_log_num_of_meals_mutex(t_args *args);

/* log */
int					log_eating(t_philo_args *args);
int					log_thinking(t_philo_args *args);
int					log_sleeping(t_philo_args *args);
int					log_died(int id, t_args *args);
int					log_taken_fork(t_philo_args *args);

/* actions */
int					philo_eat(t_philo_args *args);
int					philo_sleep(t_philo_args *args);
int					philo_think(t_philo_args *args);
void				philo_fail(t_philo_args *args);

/* monitor */
void				monitor_thread(t_philo_args *args);

#endif
