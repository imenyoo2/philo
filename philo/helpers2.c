/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 22:52:13 by ayait-el          #+#    #+#             */
/*   Updated: 2024/08/15 22:53:15 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	update_current(struct timeval *current)
{
	if (gettimeofday(current, NULL))
		return (write(2, "failed to get time of day\n", 26), 1);
	return (0);
}

int	has_died__(t_args *args)
{
	int	return_value;

	pthread_mutex_lock(&args->died);
	return_value = args->has_died;
	pthread_mutex_unlock(&args->died);
	return (return_value);
}

int	ft_usleep(long usec, t_args *args)
{
	struct timeval	current;
	struct timeval	start;

	update_current(&current);
	timeval_copy(&current, &start);
	while (usec > calculate_timestamp(&start, &current) && !has_died__(args))
	{
		update_current(&current);
		usleep(200);
	}
	if (has_died__(args))
		return (1);
	else
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

int	start_simulation(pthread_mutex_t *ready)
{
	if (pthread_mutex_lock(ready))
		return (write(2, "start_simulation: failed to lock mutex\n", 39), 1);
	if (pthread_mutex_unlock(ready))
		return (write(2, "start_simulation: failed to lock unmutex\n", 41), 1);
	return (0);
}
