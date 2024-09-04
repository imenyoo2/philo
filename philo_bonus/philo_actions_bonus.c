/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 00:26:34 by ayait-el          #+#    #+#             */
/*   Updated: 2024/08/30 10:07:41 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*
 * all actions return 0 if action suceeded, or 1 if philo died or on error
 */

int	philo_eat(t_philo_args *args)
{
	obtain_forks(args);
	log_eating(args);
	if (update_current(args->args->last_eat))
		return (release_forks(args), 1);
	args->args->eaten_meals += 1;
	if (ft_usleep(args->args->time_to_eat))
		return (release_forks(args), 1);
	if (args->args->number_of_meals != -1
		&& args->args->eaten_meals == args->args->number_of_meals)
		sem_post(args->args->philos_are_full);
	release_forks(args);
	return (0);
}

int	philo_sleep(t_philo_args *args)
{
	log_sleeping(args);
	if (ft_usleep(args->args->time_to_sleep))
		return (1);
	return (0);
}

int	philo_think(t_philo_args *args)
{
	log_thinking(args);
	ft_usleep(5);
	return (0);
}

void	philo_fail(t_philo_args *args)
{
	sem_post(args->args->stop_simulation);
	exit(1);
}
