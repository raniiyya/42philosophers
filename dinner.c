/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 13:11:50 by rdavurov          #+#    #+#             */
/*   Updated: 2025/02/16 19:07:15 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	thinking(t_philo *philo)
{
	write_status(THINKING, philo, DEBUG_MODE);
}

static void	eat(t_philo *philo)
{
	safe_mutex_handle(philo->first_fork->fork, LOCK);
	write_status(TAKE_FIRS_FORK, philo, DEBUG_MODE);
	safe_mutex_handle(philo->second_fork->fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);
	set_long(philo->philo_mtx, &philo->last_meal, gettime(MILLISECOND));
	philo->meals_count++;
	write_status(EATING, philo, DEBUG_MODE);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->meals_limit > 0
		&& philo->meals_count == philo->table->meals_limit)
		set_bool(&philo->philo_mtx, &philo->full, true);
	safe_mutex_handle(philo->first_fork->fork, UNLOCK);
	safe_mutex_handle(philo->second_fork->fork, UNLOCK);
}

void	*dinner_simulation(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data; 
	wait_all_threads(philo->table);
	while (!simulation_finished(philo->table))
	{
		if (philo->full)
			break ;
		eat(philo);
		write_status(SLEEPING, philo, false);
		precise_usleep(philo->table->time_to_sleep, philo->table);
		thinking(philo);
	}
	return (NULL);
}

void	dinner_start(t_table *table)
{
	int i;

	i = -1;
	if (table->meals_limit == 0)
		return ;
	else if (table->philo_count == 1)
		; //todo
	else
	{
		while (++i < table->philo_count)
			safe_thread_handle(&table->philos[i].thread_id, dinner_simulation,
					&table->philos[i], CREATE);
	}
	table->start_time = gettime(MILLISECOND);
	set_bool(&table->table_mtx, &table->all_threads_ready, true);
	i = -1;
	while (++i < table->philo_count)
		safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
}