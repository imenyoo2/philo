/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 23:03:44 by ayait-el          #+#    #+#             */
/*   Updated: 2024/09/08 22:44:48 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	args->mutex_arr = NULL;
	args->start = NULL;
	args->number_of_meals_arr = NULL;
	args->last_eat_arr = NULL;
	if (argc > 5)
	{
		args->number_of_meals = ft_atoi(argv[5]);
		if (args->number_of_meals < 0)
			return (free(args), unvalid_argument_error(), NULL);
	}
	else
		args->number_of_meals = -1;
	if (check_parsed_args(args))
		return (free(args), NULL);
	return (args);
}

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
	if (set_log_num_of_meals_mutex(args))
		return (write(2, "init_shared_mutexes failed\n", 27), 1);
	return (0);
}

int	set_shared_data(t_args *args)
{
	int				*nb_of_meals_arr;
	struct timeval	*start;

	if (init_shared_mutexes(args))
		return (1);
	start = malloc(sizeof(struct timeval));
	if (!start)
		return (write(2, "spwn_monitor_thread: malloc failed\n", 35), 1);
	args->mutex_arr = init_mutex_arr(args->number_of_philosophers);
	if (args->mutex_arr == NULL)
		return (free(start), 1);
	nb_of_meals_arr = init_number_of_meals_arr(args->number_of_philosophers);
	if (!nb_of_meals_arr)
		return (free(start), free_mutex_arr(args->mutex_arr,
				args->number_of_philosophers), 1);
	args->last_eat_arr = alloc_last_eat_arr(args->number_of_philosophers);
	if (!args->last_eat_arr)
		return (free(start), free(nb_of_meals_arr),
			free_mutex_arr(args->mutex_arr, args->number_of_philosophers), 1);
	args->has_died = 0;
	args->number_of_meals_arr = nb_of_meals_arr;
	args->start = start;
	return (0);
}
