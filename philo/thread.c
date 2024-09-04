/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 00:29:17 by ayait-el          #+#    #+#             */
/*   Updated: 2024/08/16 00:30:21 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_mutex_arr(pthread_mutex_t *mutex_arr, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		pthread_mutex_destroy(&mutex_arr[i]);
		i++;
	}
	free(mutex_arr);
}

int	*init_number_of_meals_arr(int size)
{
	int	*result;
	int	i;

	result = malloc(sizeof(int) * size);
	if (!result)
		return (NULL);
	i = 0;
	while (i < size)
	{
		result[i] = 0;
		i++;
	}
	return (result);
}

struct timeval	*alloc_last_eat_arr(int size)
{
	struct timeval	*arr;

	arr = malloc(sizeof(struct timeval) * size);
	if (!arr)
		return (NULL);
	return (arr);
}

pthread_mutex_t	*init_mutex_arr(int size)
{
	pthread_mutex_t	*mutex_arr;
	int				i;

	mutex_arr = malloc(sizeof(pthread_mutex_t) * (size));
	if (mutex_arr == NULL)
		return (write(2, "init_mutex_arr: failed to alloc mutex_arr\n", 42),
			NULL);
	i = 0;
	while (i < size)
	{
		if (pthread_mutex_init(&mutex_arr[i], NULL))
		{
			free_mutex_arr(mutex_arr, size);
			return (write(2, "failed to initiate mutex_arr\n", 29),
				free(mutex_arr), NULL);
		}
		i++;
	}
	return (mutex_arr);
}

/*
void	avoid_deadlock(int id)
{
  if (id % 2 == 0)
	ft_usleep(5);
}
*/

void	*philosopher(t_philo_args *args)
{
	if (start_simulation(&args->args->start_simulation))
		return (philo_fail(args), NULL);
	while (1)
	{
		if (philo_eat(args))
			return (philo_fail(args), NULL);
		if (philo_sleep(args))
			return (philo_fail(args), NULL);
		if (philo_think(args))
			return (philo_fail(args), NULL);
	}
	return (args);
}
