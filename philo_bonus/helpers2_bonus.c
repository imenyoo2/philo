/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 22:52:13 by ayait-el          #+#    #+#             */
/*   Updated: 2024/09/03 22:38:40 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*
int	philo_has_died(struct timeval *last_eat, t_philo_args *args)
{
	struct timeval	current;

	if (update_current(&current))
		return (1);
	if (calculate_timestamp(last_eat, &current) > args->args->time_to_die)
		return (log_died(args->id, args->args), 1);
	else
		return (0);
}
*/

int	update_current(struct timeval *current)
{
	if (gettimeofday(current, NULL))
		return (write(2, "failed to get time of day\n", 26), 1);
	return (0);
}

/*
int	has_died__(t_args *args)
{
	int	return_value;

	pthread_mutex_lock(&args->died);
	return_value = args->has_died;
	pthread_mutex_unlock(&args->died);
	return (return_value);
}
*/

int	ft_usleep(long usec)
{
	struct timeval	current;
	struct timeval	start;

	update_current(&current);
	timeval_copy(&current, &start);
	while (usec > calculate_timestamp(&start, &current))
	{
		update_current(&current);
		usleep(200);
	}
	return (0);
}

/*
int	mutex_is_locked(pthread_mutex_t *mutex)
{
  if (mutex->__data.__lock)
	return (1);
  else
	return (0);
}
*/

void	add_microseconds(struct timeval *tv, long microseconds_to_add)
{
	tv->tv_usec += microseconds_to_add;
	while (tv->tv_usec >= 1000000)
	{
		tv->tv_usec -= 1000000;
		tv->tv_sec += 1;
	}
}

void	correct_start(struct timeval *start)
{
	struct timeval	current;

	update_current(&current);
	while (calculate_timestamp(start, &current) < 30)
	{
		update_current(&current);
		usleep(100);
	}
	add_microseconds(start, 30 * 1000);
}

void	start_simulation(sem_t *ready)
{
	sem_wait(ready);
	sem_post(ready);
}
