/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 23:00:39 by ayait-el          #+#    #+#             */
/*   Updated: 2024/08/15 23:00:48 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	log_eating(t_philo_args *args)
{
	struct timeval	current;

	pthread_mutex_lock(&args->args->print_mutex);
	if (update_current(&current))
		return (pthread_mutex_unlock(&args->args->print_mutex), 1);
	if (has_died__(args->args))
		return (pthread_mutex_unlock(&args->args->print_mutex), 1);
	printf("%ld %d is eating\n", calculate_timestamp(args->args->start,
			&current), args->id);
	pthread_mutex_unlock(&args->args->print_mutex);
	return (0);
}

int	log_thinking(t_philo_args *args)
{
	struct timeval	current;

	pthread_mutex_lock(&args->args->print_mutex);
	if (update_current(&current))
		return (pthread_mutex_unlock(&args->args->print_mutex), 1);
	if (has_died__(args->args))
		return (pthread_mutex_unlock(&args->args->print_mutex), 1);
	printf("%ld %d is thinking\n", calculate_timestamp(args->args->start,
			&current), args->id);
	pthread_mutex_unlock(&args->args->print_mutex);
	return (0);
}

int	log_sleeping(t_philo_args *args)
{
	struct timeval	current;

	pthread_mutex_lock(&args->args->print_mutex);
	if (update_current(&current))
		return (pthread_mutex_unlock(&args->args->print_mutex), 1);
	if (has_died__(args->args))
		return (pthread_mutex_unlock(&args->args->print_mutex), 1);
	printf("%ld %d is sleeping\n", calculate_timestamp(args->args->start,
			&current), args->id);
	pthread_mutex_unlock(&args->args->print_mutex);
	return (0);
}

int	log_died(int id, t_args *args)
{
	struct timeval	current;

	pthread_mutex_lock(&args->print_mutex);
	pthread_mutex_lock(&args->died);
	args->has_died = 1;
	if (update_current(&current))
		return (pthread_mutex_unlock(&args->died),
			pthread_mutex_unlock(&args->print_mutex), 1);
	printf("%ld %d died\n", calculate_timestamp(args->start, &current), id);
	pthread_mutex_unlock(&args->print_mutex);
	pthread_mutex_unlock(&args->died);
	return (0);
}

int	log_taken_fork(t_philo_args *args)
{
	struct timeval	current;

	pthread_mutex_lock(&args->args->print_mutex);
	if (update_current(&current))
		return (pthread_mutex_unlock(&args->args->print_mutex), 1);
	if (has_died__(args->args))
		return (pthread_mutex_unlock(&args->args->print_mutex), 1);
	printf("%ld %d has taken a fork\n", calculate_timestamp(args->args->start,
			&current), args->id);
	pthread_mutex_unlock(&args->args->print_mutex);
	return (0);
}

/*
int	log_state(struct timeval *start, int id, t_philo_args *args)
{
  struct timeval current;
  struct timeval last_eat;

  if (gettimeofday(&current, NULL))
	return (write(2, "failed to get timeofday\n", 24), 1);
  timeval_copy(&current, &last_eat);
  while (gettimeofday(&current, NULL))
  {
	log_eating(start, &current, id);
	usleep(args->args->time_to_eat * 1000);
	log_sleeping(start, &current, id);
	usleep(args->args->time_to_eat * 1000);
	log_thinking(start, &current, id);
  }
  return (write(2, "failed to get timeofday\n", 24), 1);
}
*/
