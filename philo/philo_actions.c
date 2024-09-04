/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 00:26:34 by ayait-el          #+#    #+#             */
/*   Updated: 2024/08/16 00:26:46 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * all actions return 0 if action suceeded, or 1 if philo died or on error
 */

int	philo_eat(t_philo_args *args)
{
	if (mutex_lock(args))
		return (1);
	log_eating(args);
	args->args->number_of_meals_arr[args->id - 1] += 1;
	if (update_current(&args->args->last_eat_arr[args->id - 1]))
		return (mutex_unlock(args->args->mutex_arr, args->id,
				args->args->number_of_philosophers - 1), 1);
	if (ft_usleep(args->args->time_to_eat, args->args))
		return (mutex_unlock(args->args->mutex_arr, args->id,
				args->args->number_of_philosophers - 1), 1);
	mutex_unlock(args->args->mutex_arr, args->id,
		args->args->number_of_philosophers - 1);
	return (0);
}

int	philo_sleep(t_philo_args *args)
{
	log_sleeping(args);
	if (ft_usleep(args->args->time_to_sleep, args->args))
		return (1);
	return (0);
}

int	philo_think(t_philo_args *args)
{
	log_thinking(args);
	ft_usleep(5, args->args);
	return (0);
}

void	philo_fail(t_philo_args *args)
{
	set_has_died(args->args);
	free(args);
}
