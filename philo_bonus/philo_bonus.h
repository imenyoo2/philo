/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 00:25:57 by ayait-el          #+#    #+#             */
/*   Updated: 2024/09/04 04:09:15 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <errno.h>
# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct args
{
	int				number_of_philosophers;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	int				number_of_meals;
	struct timeval	start;

	sem_t			*print_sem;
	sem_t			*stop_simulation;
	sem_t			*start_simulation;
	sem_t			*forks;
	sem_t			*philos_are_full;

	struct timeval	*last_eat;
	int				eaten_meals;
	pid_t			*pids_arr;
}					t_args;

typedef struct philo_args
{
	t_args			*args;
	int				id;
}					t_philo_args;

t_args				*parse_argv(int argc, char **argv);
int					set_shared_data(t_args *args);
int					ft_atoi(const char *str);
int					set_shared_data(t_args *args);
int					int_semaphores(t_args *args);

/* process */
void				*philosopher(t_philo_args *args);
int					run_processes(t_args *args);
int					run_and_monitor_processes(t_args *args);
int					spawn_processes(t_args *args);
void				wait_for_processes(int size, pid_t *pids_arr);
void				kill_all_processes(int size, pid_t *pids_arr);

/* forks */
void				obtain_forks(t_philo_args *args);
void				release_forks(t_philo_args *args);

/* helpers */
long				calculate_timestamp(struct timeval *start,
						struct timeval *current);
void				timeval_copy(struct timeval *from, struct timeval *to);
int					update_current(struct timeval *current);
int					ft_usleep(long usec);
int					philo_has_died(struct timeval *last_eat,
						t_philo_args *args);
void				start_simulation(sem_t *ready);
void				correct_start(struct timeval *start);
void				add_microseconds(struct timeval *tv,
						long microseconds_to_add);
void				wait_stop_simulation(t_args *args);
void				avoid_deadlock(t_philo_args *args);
int					spwn_monitor_number_of_meals_thread(t_args *args,
						pthread_t *thread);

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
void				*monitor(t_philo_args *args);
int					spwn_monitor_thread(t_philo_args *args);

#endif
