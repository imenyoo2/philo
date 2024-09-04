/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 22:58:14 by ayait-el          #+#    #+#             */
/*   Updated: 2024/08/15 22:58:34 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	index_lock_mutex(pthread_mutex_t *mutex_arr, int index)
{
	pthread_mutex_lock(&mutex_arr[index]);
}

static void	set_forks(int *fork1, int *fork2, t_philo_args *args)
{
	int	n;
	int	*tmp;

	n = args->args->number_of_philosophers - 1;
	if ((args->id - 1) % 2)
	{
		tmp = fork1;
		fork1 = fork2;
		fork2 = tmp;
	}
	if (args->id == 1)
	{
		*fork1 = 0;
		*fork2 = n;
	}
	else
	{
		*fork1 = args->id - 1;
		*fork2 = args->id - 2;
	}
}

int	mutex_lock(t_philo_args *args)
{
	pthread_mutex_t	*mutex_arr;
	int				fork1;
	int				fork2;

	set_forks(&fork1, &fork2, args);
	mutex_arr = args->args->mutex_arr;
	index_lock_mutex(mutex_arr, fork1);
	log_taken_fork(args);
	if (fork1 == fork2)
	{
		pthread_mutex_unlock(&mutex_arr[fork1]);
		return (1);
	}
	index_lock_mutex(mutex_arr, fork2);
	log_taken_fork(args);
	return (0);
}

void	mutex_unlock(pthread_mutex_t *mutex_arr, int id, int n)
{
	if (id == 1)
	{
		pthread_mutex_unlock(&mutex_arr[0]);
		if (n != 0)
			pthread_mutex_unlock(&mutex_arr[n]);
	}
	else
	{
		pthread_mutex_unlock(&mutex_arr[id - 1]);
		pthread_mutex_unlock(&mutex_arr[id - 2]);
	}
}
