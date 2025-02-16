/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:53:28 by rdavurov          #+#    #+#             */
/*   Updated: 2025/02/16 19:08:14 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(t_philo *philo, t_fork *forks, int philo_position)
{
	int	philo_num;

	philo_num = philo->table->philo_count;
	philo->first_fork = &forks[(philo_position + 1) % philo_num];
	philo->second_fork = &forks[philo_position];
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[philo_position];
		philo->second_fork = &forks[(philo_position + 1) % philo_num];
	}
}

static void	philo_init(t_table *table)
{
	int	i;
	t_philo	*philo;

	i = -1;
	while (++i < table->philo_count)
	{
		philo = table->philos + i;
		philo->id = i;
		philo->full = false;
		philo->meals_count = 0;
		philo->table = table;
		safe_mutex_handle(philo->philo_mtx, INIT);
		assign_fork(philo, table->forks, i);
	}
}

void	data_init(t_table *table)
{
	int	i;

	i = -1;
	table->dead = false;
	table->all_threads_ready = false;
	table->philos = safe_malloc(sizeof(t_philo) * table->philo_count);
	safe_mutex_handle(table->table_mtx, INIT);
	table->forks = safe_malloc(sizeof(t_fork) * table->philo_count);
	while (++i < table->philo_count)
	{
		safe_mutex_handle(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i;
	}
	philo_init(table);
}