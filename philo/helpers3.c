/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 22:53:29 by ayait-el          #+#    #+#             */
/*   Updated: 2024/08/16 00:21:22 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_philo_full(t_philo_args *args)
{
	int	nb_of_meals;

	nb_of_meals = args->args->number_of_meals;
	if (nb_of_meals == -1)
		return (0);
	if (args->args->number_of_meals_arr[args->id - 1] == nb_of_meals)
		return (1);
	else
		return (0);
}

void	set_has_died(t_args *args)
{
	pthread_mutex_lock(&args->died);
	args->has_died = 1;
	pthread_mutex_unlock(&args->died);
}
