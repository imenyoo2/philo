/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 00:13:28 by ayait-el          #+#    #+#             */
/*   Updated: 2024/09/04 04:08:43 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*
static int	is_philos_full(t_args *args)
{
	int	i;

	if (args->number_of_meals == -1)
		return (0);
	i = 0;
	while (i < args->number_of_philosophers)
	{
		if (args->number_of_meals_arr[i] < args->number_of_meals)
			return (0);
		i++;
	}
	if (pthread_mutex_lock(&args->died))
		write(2, "failed to lock args->died\n", 26);
	args->has_died = 1;
	if (pthread_mutex_unlock(&args->died))
		write(2, "failed to unlock args->died\n", 28);
	return (1);
}
*/

/*
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
*/

static int	launch_simulation(t_args *args)
{
	int	status;

	sem_wait(args->start_simulation);
	status = spawn_processes(args);
	if (status)
	{
		kill_all_processes(status - 1, args->pids_arr);
		sem_post(args->start_simulation);
		return (1);
	}
	sem_post(args->start_simulation);
	return (0);
}

int	run_and_monitor_processes(t_args *args)
{
	pthread_t	thread;
	int			i;

	if (launch_simulation(args))
		return (1);
	if (spwn_monitor_number_of_meals_thread(args, &thread))
		return (1);
	wait_stop_simulation(args);
	i = 0;
	while (i < args->number_of_philosophers)
	{
		sem_post(args->philos_are_full);
		i++;
	}
	pthread_join(thread, NULL);
	return (0);
}

void	*monitor(t_philo_args *args)
{
	struct timeval	current;

	while (1)
	{
		if (update_current(&current))
		{
			sem_wait(args->args->print_sem);
			sem_post(args->args->stop_simulation);
			exit(1);
		}
		if (calculate_timestamp(args->args->last_eat,
				&current) >= args->args->time_to_die)
		{
			log_died(args->id, args->args);
			sem_post(args->args->stop_simulation);
			exit(1);
		}
		usleep(100);
	}
}

int	spwn_monitor_thread(t_philo_args *args)
{
	pthread_t	monitor_thread;

	if (pthread_create(&monitor_thread, NULL, (void *)&monitor, args))
		return (1);
	return (0);
}
