/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 23:02:17 by ayait-el          #+#    #+#             */
/*   Updated: 2024/09/12 02:08:03 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	usage(void)
{
	printf("usage:\n\t");
	printf("philosophers <number_of_philosophers>"
		" <time_to_die> <time_to_eat> <time_to_sleep> "
		"[number_of_times_each_philosopher_must_eat]\n");
}

static void	free_mutexes(t_args *args)
{
	pthread_mutex_destroy(&args->print_mutex);
	pthread_mutex_destroy(&args->died);
	pthread_mutex_destroy(&args->log_last_eat);
	pthread_mutex_destroy(&args->start_simulation);
	pthread_mutex_destroy(&args->log_num_of_meals);
}

static void	free_args(t_args *args)
{
	free_mutex_arr(args->mutex_arr, args->number_of_philosophers);
	free_mutexes(args);
	free(args->start);
	free(args->number_of_meals_arr);
	free(args->last_eat_arr);
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
	if (set_shared_data(args))
		return (free(args), 1);
	if (run_threads(args))
		return (free_args(args), 1);
	free_args(args);
	return (0);
}
