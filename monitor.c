/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:17:54 by rdavurov          #+#    #+#             */
/*   Updated: 2025/02/17 12:31:07 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	t_to_die;

	if (get_bool(philo->philo_mtx, &philo->full))
		return (false);
	
	elapsed = gettime(MILLISECOND) - get_long(philo->philo_mtx, &philo->last_meal);
	t_to_die = philo->table->time_to_die / 1e3;
	if (elapsed > t_to_die)
		return (true);
	return (false);
}

void	*monitor_dinner(void *data)
{
	int		i;
	t_table	*table;

	table = (t_table *)data;
	while (!all_threads_running(table->table_mtx, &table->threads_running_num, table->philo_count))
		;
	while (!simulation_finished(table))
	{
		i = -1;
		while (++i < table->philo_count && !simulation_finished(table))
		{
			if (philo_died(table->philos + i))
			{
				set_bool(table->table_mtx, &table->dead, true);
				write_status(DIED, table->philos + i, DEBUG_MODE);
			}
		}
	}
	return (NULL);
}