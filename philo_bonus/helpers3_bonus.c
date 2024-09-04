/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers3_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <ayait-el@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 10:08:50 by ayait-el          #+#    #+#             */
/*   Updated: 2024/08/30 10:09:43 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	wait_stop_simulation(t_args *args)
{
	sem_wait(args->stop_simulation);
	kill_all_processes(args->number_of_philosophers, args->pids_arr);
}

void	*monitor_number_of_meals(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->number_of_philosophers)
	{
		sem_wait(args->philos_are_full);
		i++;
	}
	sem_post(args->stop_simulation);
	return (NULL);
}

int	spwn_monitor_number_of_meals_thread(t_args *args, pthread_t *thread)
{
	if (pthread_create(thread, NULL, (void *)monitor_number_of_meals, args))
		return (write(2, "failed to create thread\n", 24), 1);
	return (0);
}

void	avoid_deadlock(t_philo_args *args)
{
	if (args->id % 2 == 0)
		ft_usleep(args->args->time_to_eat - 10);
}
