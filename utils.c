/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 09:05:43 by rdavurov          #+#    #+#             */
/*   Updated: 2025/02/17 12:32:36 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	gettime(t_time_code time_code)
{
	struct	timeval	tv;

	if (gettimeofday(&tv, NULL))
		error_exit("gettimeofday failed");
	if (SECOND == time_code)
		return (tv.tv_sec + tv.tv_usec / 1e6);
	else if (MILLISECOND == time_code)
		return (tv.tv_sec * 1e3 + tv.tv_usec / 1e3);
	else if (MICROSECOND == time_code)
		return (tv.tv_sec * 1e6 + tv.tv_usec);
	else
		error_exit("Invalid time code");
	return (0);
		
}

void	precise_usleep(long usec, t_table *table)
{
	long	start_time;
	long	elapsed;
	long	remaining;

	start_time = gettime(MICROSECOND);
	while (gettime(MICROSECOND) - start_time < usec)
	{
		if (simulation_finished(table))
			break ;
		elapsed = gettime(MICROSECOND) - start_time;
		remaining = usec - elapsed;
		if (remaining > 1e3)
			usleep(remaining / 2);
		else
			while (gettime(MICROSECOND) - start_time < usec)
				;
	}
}

void	clean(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < table->philo_count)
	{
		philo = table->philos + i;
		safe_mutex_handle(philo->philo_mtx, DESTROY);
	}
	safe_mutex_handle(table->print_mtx, DESTROY);
	safe_mutex_handle(table->table_mtx, DESTROY);
	free(table->forks);
	free(table->philos);
}

void	error_exit(const char *msg)
{
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}	