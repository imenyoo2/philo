/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 22:58:14 by ayait-el          #+#    #+#             */
/*   Updated: 2024/08/30 10:12:24 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	obtain_forks(t_philo_args *args)
{
	sem_wait(args->args->forks);
	log_taken_fork(args);
	sem_wait(args->args->forks);
	log_taken_fork(args);
}

void	release_forks(t_philo_args *args)
{
	sem_post(args->args->forks);
	sem_post(args->args->forks);
}
