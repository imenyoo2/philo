/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 23:02:17 by ayait-el          #+#    #+#             */
/*   Updated: 2024/09/08 22:45:24 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	usage(void)
{
	printf("usage:\n\t");
	printf("philosophers <number_of_philosophers>"
		" <time_to_die> <time_to_eat> <time_to_sleep> "
		"[number_of_times_each_philosopher_must_eat]\n");
}

/*
static void	free_mutexes(t_args *args)
{
	pthread_mutex_destroy(&args->print_mutex);
	pthread_mutex_destroy(&args->died);
	pthread_mutex_destroy(&args->log_last_eat);
	pthread_mutex_destroy(&args->start_simulation);
}*/
static void	free_args(t_args *args)
{
	free(args->last_eat);
	free(args->pids_arr);
	sem_close(args->start_simulation);
	sem_close(args->print_sem);
	sem_close(args->stop_simulation);
	sem_close(args->forks);
	sem_close(args->philos_are_full);
	free(args);
}

int	main(int argc, char **argv)
{
	pthread_t	p;
	t_args		*args;

	(void)p;
	if (argc < 5)
		return (usage(), 1);
	args = parse_argv(argc, argv);
	if (!args)
		return (1);
  if (args->number_of_meals == 0)
    return (free(args), 0);
	if (int_semaphores(args))
		return (write(2, "int_semaphores: failed to create\n", 33), free(args),
			1);
	if (set_shared_data(args))
		return (free(args), 1);
	if (run_processes(args))
		return (free_args(args), 1);
	free_args(args);
	return (0);
}
