/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process2_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 00:30:52 by ayait-el          #+#    #+#             */
/*   Updated: 2024/09/03 23:09:39 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_all_processes(int size, pid_t *pids_arr)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (pids_arr[i] != 0)
			kill(pids_arr[i], SIGKILL);
		i++;
	}
}

void	wait_for_processes(int size, pid_t *pids_arr)
{
	int	i;
	int	status;

	i = 0;
	while (i < size)
	{
		waitpid(pids_arr[i], &status, 0);
		i++;
	}
}

int	spawn_processes(t_args *args)
{
	int				i;
	t_philo_args	philo_args;
	int				pid;

	i = 1;
	philo_args.args = args;
	while (i <= args->number_of_philosophers)
	{
		philo_args.id = i;
		pid = fork();
		if (pid == -1)
			return (write(2, "spwan_process: failed to fork\n", 30), i + 1);
		else if (pid == 0)
		{
			philosopher(&philo_args);
			exit(1);
		}
		else
			args->pids_arr[i - 1] = pid;
		i++;
	}
	return (0);
}

int	run_processes(t_args *args)
{
	if (run_and_monitor_processes(args))
		return (1);
	wait_for_processes(args->number_of_philosophers, args->pids_arr);
	return (0);
}

/*
int	spwn_monitor_thread(t_philo_args *philo_args)
{
  pthread_t monitor;

  if (pthread_create(&monitor, NULL, (void *) &monitor_thread, philo_args))
	return (write(2, "failed to create monitor thread\n", 32), 1);
  pthread_join(monitor, NULL);
  return (0);
}
*/
