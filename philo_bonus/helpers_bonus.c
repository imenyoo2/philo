/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 22:51:11 by ayait-el          #+#    #+#             */
/*   Updated: 2024/08/30 10:09:14 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static const char	*skip_white_spaces(const char *str)
{
	while (*str == ' ' || *str == '\n' || *str == '\r' || *str == '\v'
		|| *str == '\f' || *str == '\t')
		str++;
	return (str);
}

static int	get_result(const char *str)
{
	int	result;

	result = 0;
	if (*str >= '0' && *str <= '9')
	{
		result += *str - '0';
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result *= 10;
		result += *str - '0';
		str++;
	}
	if (*str != '\0')
		return (-1);
	return (result);
}

int	ft_atoi(const char *str)
{
	int	minus_counter;
	int	result;

	str = skip_white_spaces(str);
  if (*str == '\0')
    return (-1);
	minus_counter = 0;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			minus_counter++;
		str++;
	}
	result = get_result(str);
	if (result == -1)
		return (-1);
	if (minus_counter % 2)
		return (result * -1);
	else
		return (result);
}

void	timeval_copy(struct timeval *from, struct timeval *to)
{
	to->tv_sec = from->tv_sec;
	to->tv_usec = from->tv_usec;
}

// note: time is in ms
long	calculate_timestamp(struct timeval *start, struct timeval *current)
{
	return ((long)((current->tv_usec - start->tv_usec) / 1000)
		+ (current->tv_sec - start->tv_sec) * 1000);
}
