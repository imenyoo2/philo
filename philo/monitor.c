/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 00:13:28 by ayait-el          #+#    #+#             */
/*   Updated: 2024/09/04 06:39:51 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_philos_full(t_args *args)
{
	int	i;

	if (args->number_of_meals == -1)
		return (0);
	i = 0;
	pthread_mutex_lock(&args->log_num_of_meals);
	while (i < args->number_of_philosophers)
	{
		if (args->number_of_meals_arr[i] < args->number_of_meals)
			return (pthread_mutex_unlock(&args->log_num_of_meals), 0);
		i++;
	}
	pthread_mutex_unlock(&args->log_num_of_meals);
	if (pthread_mutex_lock(&args->died))
		write(2, "failed to lock args->died\n", 26);
	args->has_died = 1;
	if (pthread_mutex_unlock(&args->died))
		write(2, "failed to unlock args->died\n", 28);
	return (1);
}

static void	fill_last_eat_arr(struct timeval *last_eat_arr,
		struct timeval *value, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		timeval_copy(value, &last_eat_arr[i]);
		i++;
	}
}

static int	launch_simulation(t_args *args, pthread_t *threads_arr)
{
	struct timeval	current;
	int				status;

	pthread_mutex_lock(&args->start_simulation);
	status = spawn_threads(args, threads_arr);
	if (status)
	{
		pthread_mutex_lock(&args->died);
		args->has_died = 1;
		pthread_mutex_unlock(&args->died);
		pthread_mutex_unlock(&args->start_simulation);
		wait_for_threads(status - 1, threads_arr);
		return (1);
	}
	if (update_current(&current))
		return (pthread_mutex_unlock(&args->start_simulation), 1);
	timeval_copy(&current, args->start);
	fill_last_eat_arr(args->last_eat_arr, args->start,
		args->number_of_philosophers);
	pthread_mutex_unlock(&args->start_simulation);
	return (0);
}

// TODO: 0 should not be blocked in number of meals
int	run_and_monitor_threads(t_args *args, pthread_t *threads_arr)
{
	int				i;
	struct timeval	*last_eat;
	struct timeval	current;

	if (launch_simulation(args, threads_arr))
		return (1);
	while (1)
	{
		i = 0;
		while (i < args->number_of_philosophers)
		{
      pthread_mutex_lock(&args->log_last_eat);
			last_eat = &args->last_eat_arr[i];
			if (update_current(&current))
				return (pthread_mutex_unlock(&args->log_last_eat), set_has_died(args), 1);
			if (calculate_timestamp(last_eat, &current) >= args->time_to_die)
			{
        pthread_mutex_unlock(&args->log_last_eat);
				if (log_died(i + 1, args))
					return (1);
				return (0);
			}
      pthread_mutex_unlock(&args->log_last_eat);
			i++;
		}
		if (is_philos_full(args))
			return (0);
	}
}
