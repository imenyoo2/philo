/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 23:03:44 by ayait-el          #+#    #+#             */
/*   Updated: 2024/09/08 22:45:02 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	unvalid_argument_error(void)
{
	write(2, "ERROR: unvalid_argument\n", 24);
}

static int	check_parsed_args(t_args *args)
{
	if (args->number_of_philosophers <= 0)
		return (unvalid_argument_error(), 1);
	else if (args->time_to_die <= 0)
		return (unvalid_argument_error(), 1);
	else if (args->time_to_eat <= 0)
		return (unvalid_argument_error(), 1);
	else if (args->time_to_sleep <= 0)
		return (unvalid_argument_error(), 1);
	else
		return (0);
}

t_args	*parse_argv(int argc, char **argv)
{
	t_args	*args;

	args = malloc(sizeof(t_args));
	if (!args)
		return (write(2, "parse_argv: failed to allocate args\n", 36), NULL);
	args->number_of_philosophers = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	args->eaten_meals = 0;
	if (update_current(&args->start))
		return (free(args), NULL);
	if (argc > 5)
	{
		args->number_of_meals = ft_atoi(argv[5]);
		if (args->number_of_meals <= 0)
			return (free(args), unvalid_argument_error(), NULL);
	}
	else
		args->number_of_meals = -1;
	if (check_parsed_args(args))
		return (free(args), NULL);
	return (args);
}

int	int_semaphores(t_args *args)
{
	sem_unlink("/start_simulation");
	sem_unlink("/print_sem");
	sem_unlink("/stop_simulation");
	sem_unlink("/forks");
	sem_unlink("/philos_are_full");
	args->start_simulation = sem_open("/start_simulation", O_CREAT, 0644, 1);
	if (args->start_simulation == SEM_FAILED)
		return (1);
	args->print_sem = sem_open("/print_sem", O_CREAT, 0644, 1);
	if (args->print_sem == SEM_FAILED)
		return (sem_close(args->start_simulation), 1);
	args->stop_simulation = sem_open("/stop_simulation", O_CREAT, 0644, 0);
	if (args->stop_simulation == SEM_FAILED)
		return (sem_close(args->start_simulation), sem_close(args->print_sem),
			1);
	args->forks = sem_open("/forks", O_CREAT, 0644,
			args->number_of_philosophers);
	if (args->forks == SEM_FAILED)
		return (sem_close(args->stop_simulation),
			sem_close(args->start_simulation), sem_close(args->print_sem), 1);
	args->philos_are_full = sem_open("/philos_are_full", O_CREAT, 0644, 0);
	if (args->philos_are_full == SEM_FAILED)
		return (sem_close(args->forks), sem_close(args->stop_simulation),
			sem_close(args->start_simulation), sem_close(args->print_sem), 1);
	return (0);
}

/*
int	init_shared_mutexes(t_args *args)
{
	if (pthread_mutex_init(&args->print_mutex, NULL))
		return (write(2, "init_shared_mutexes failed\n", 27), 1);
	if (pthread_mutex_init(&args->start_simulation, NULL))
	{
		pthread_mutex_destroy(&args->print_mutex);
		return (write(2, "init_shared_mutexes failed\n", 27), 1);
	}
	if (pthread_mutex_init(&args->died, NULL))
	{
		pthread_mutex_destroy(&args->start_simulation);
		pthread_mutex_destroy(&args->print_mutex);
		return (write(2, "init_shared_mutexes failed\n", 27), 1);
	}
	if (pthread_mutex_init(&args->log_last_eat, NULL))
	{
		pthread_mutex_destroy(&args->died);
		pthread_mutex_destroy(&args->start_simulation);
		pthread_mutex_destroy(&args->print_mutex);
		return (write(2, "init_shared_mutexes failed\n", 27), 1);
	}
	return (0);
}
*/

int	set_shared_data(t_args *args)
{
	args->last_eat = malloc(sizeof(struct timeval));
	if (!args->last_eat)
		return (1);
	args->pids_arr = malloc(args->number_of_philosophers * sizeof(pid_t));
	if (args->pids_arr == NULL)
		return (free(args->last_eat), 1);
	return (0);
}
