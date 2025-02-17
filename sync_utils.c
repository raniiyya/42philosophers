/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 16:58:38 by rdavurov          #+#    #+#             */
/*   Updated: 2025/02/17 12:32:11 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//spinlock to sync philos

void	wait_all_threads(t_table *table)
{
	while (!get_bool(table->table_mtx, &table->all_threads_ready))
		;
}

bool	all_threads_running(t_mtx *mtx, long *threads, long philo_num)
{
	bool	ret;

	ret = false;
	safe_mutex_handle(mtx, LOCK);
	if (*threads == philo_num)
		ret = true;
	safe_mutex_handle(mtx, UNLOCK);
	return (ret);
}

void	increase_long(t_mtx *mtx, long *var, long value)
{
	safe_mutex_handle(mtx, LOCK);
	*var += value;
	safe_mutex_handle(mtx, UNLOCK);
}

void	de_sync_philos(t_philo *philo)
{
	if (philo->table->philo_count % 2 == 0)
	{
		if (philo->id % 2 == 0)
			precise_usleep(3e4, philo->table);
	}
	else
	{
		if (philo->id % 2 == 0)
			thinking(philo, true);
	}
}