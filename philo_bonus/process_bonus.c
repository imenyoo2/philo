/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 00:29:17 by ayait-el          #+#    #+#             */
/*   Updated: 2024/09/03 22:36:57 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*philosopher(t_philo_args *args)
{
	start_simulation(args->args->start_simulation);
	correct_start(&args->args->start);
	timeval_copy(&args->args->start, args->args->last_eat);
	avoid_deadlock(args);
	if (spwn_monitor_thread(args))
		exit(1);
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
