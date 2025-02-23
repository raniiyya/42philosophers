/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 13:11:50 by rdavurov          #+#    #+#             */
/*   Updated: 2025/02/23 16:48:56 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_philo *philo, bool pre_simulation)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;
	
	if (!pre_simulation)
		write_status(THINKING, philo, DEBUG_MODE);
	write_status(THINKING, philo, DEBUG_MODE);
	if (philo->table->philo_count % 2 == 0)
		return ;
	t_eat = philo->table->time_to_eat;
	t_sleep = philo->table->time_to_sleep;
	t_think = t_eat * 2 - t_sleep;
	if (t_think < 0)
		t_think = 0;
	precise_usleep(t_think * 0.42, philo->table);
}

void	*lone_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mtx, &philo->last_meal, gettime(MILLISECOND));
	increase_long(&philo->table->table_mtx, &philo->table->threads_running_num);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	while (!simulation_finished(philo->table))
		usleep(200);
	return (NULL);
}

static void	eat(t_philo *philo)
{
	safe_mutex_handle(&philo->first_fork->fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	safe_mutex_handle(&philo->second_fork->fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);
	set_long(&philo->philo_mtx, &philo->last_meal, gettime(MILLISECOND));
	philo->meals_count++;
	write_status(EATING, philo, DEBUG_MODE);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->meals_limit > 0
		&& philo->meals_count == philo->table->meals_limit)
		set_bool(&philo->philo_mtx, &philo->full, true);
	safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
	safe_mutex_handle(&philo->second_fork->fork, UNLOCK);
}

void	*dinner_simulation(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mtx, &philo->last_meal, gettime(MILLISECOND));
	increase_long(&philo->table->table_mtx, &philo->table->threads_running_num);
	de_sync_philos(philo);
	while (!simulation_finished(philo->table))
	{
		if (philo->full)
			break ;
		eat(philo);
		write_status(SLEEPING, philo, DEBUG_MODE);
		precise_usleep(philo->table->time_to_sleep, philo->table);
		thinking(philo, false);
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
		safe_thread_handle(&table->philos[0].thread_id, lone_philo, &table->philos[0], CREATE);
	else
	{
		while (++i < table->philo_count)
			safe_thread_handle(&table->philos[i].thread_id, dinner_simulation,
					&table->philos[i], CREATE);
	}
	safe_thread_handle(&table->monitor, monitor_dinner, table, CREATE);
	table->start_time = gettime(MILLISECOND);
	set_bool(&table->table_mtx, &table->all_threads_ready, true);
	i = -1;
	while (++i < table->philo_count) {
		safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
	}
	set_bool(&table->table_mtx, &table->end_time, true);
	safe_thread_handle(&table->monitor, NULL, NULL, JOIN);
}