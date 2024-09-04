/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 00:30:52 by ayait-el          #+#    #+#             */
/*   Updated: 2024/08/16 00:31:07 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_for_threads(int size, pthread_t *threads_arr)
{
	int	i;

	i = 0;
	while (i < size)
	{
		pthread_join(threads_arr[i], NULL);
		i++;
	}
}

t_philo_args	*alloc_philo_args(int id, t_args *args)
{
	t_philo_args	*philo_args;

	philo_args = malloc(sizeof(t_philo_args));
	if (philo_args == NULL)
		return (NULL);
	philo_args->args = args;
	philo_args->id = id;
	return (philo_args);
}

int	spawn_threads(t_args *args, pthread_t *threads_arr)
{
	int				i;
	t_philo_args	*philo_args;

	i = 1;
	while (i <= args->number_of_philosophers)
	{
		philo_args = alloc_philo_args(i, args);
		if (philo_args == NULL)
			return (i + 1);
		if (pthread_create(&threads_arr[i - 1], NULL, (void *)&philosopher,
				philo_args))
			return (write(2, "creating thread failed!\n", 24), i + 1);
		i++;
	}
	return (0);
}

int	run_threads(t_args *args)
{
	pthread_t	*threads_arr;

	threads_arr = malloc(args->number_of_philosophers * sizeof(pthread_t));
	if (threads_arr == NULL)
		return (1);
	if (run_and_monitor_threads(args, threads_arr))
		return (free(threads_arr), 1);
	wait_for_threads(args->number_of_philosophers, threads_arr);
	return (free(threads_arr), 0);
}

/*
int	spwn_monitor_thread(t_philo_args *philo_args)
{
  pthread_t monitor;

  if (pthread_create(&monitor, NULL, (void *) &monitor_thread, philo_args))
	return (write(2, "failed to create monitor thread\n", 32), 1);
  pthread_join(monitor, NULL);
  return (0);
}
*/
