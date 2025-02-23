/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 17:35:59 by rdavurov          #+#    #+#             */
/*   Updated: 2025/02/23 16:53:48 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	write_status_debug(t_philo_status status, t_philo *philo, long time)
{
	if (status == TAKE_FIRST_FORK && !simulation_finished(philo->table))
		printf("%-6ld %d has taken the first fork\n", time, philo->id, philo->first_fork->fork_id);
	else if (status == TAKE_SECOND_FORK && !simulation_finished(philo->table))
		printf("%-6ld %d has taken the second fork\n", time, philo->id, philo->second_fork->fork_id);
	else if (status == EATING && !simulation_finished(philo->table))
		printf("%-6ld %d is eating\n", time, philo->id, philo->meals_count);
	else if (status == SLEEPING && !simulation_finished(philo->table))
		printf("%-6ld %d is sleeping\n", time, philo->id);
	else if (status == THINKING && !simulation_finished(philo->table))
		printf("%-6ld %d is thinking\n", time, philo->id);
	else if (status == DIED)
		printf("%-6ld %d died\n", time, philo->id);
}

void	write_status(t_philo_status status, t_philo *philo, bool debug)
{
	long	time;

	time = gettime(MILLISECOND) - philo->table->start_time;
	if (philo->full)
		return ;
	safe_mutex_handle(&philo->table->print_mtx, LOCK);
	if (debug)
		write_status_debug(status, philo, time);
	else
	{
		if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
			&& !simulation_finished(philo->table))
			printf("%-6ld %d has taken a fork\n", time, philo->id);
		else if (status == EATING && !simulation_finished(philo->table))
			printf("%-6ld %d is eating\n", time, philo->id);
		else if (status == THINKING && !simulation_finished(philo->table))
			printf("%-6ld %d is thinking\n", time, philo->id);
		else if (status == SLEEPING && !simulation_finished(philo->table))
			printf("%-6ld %d is sleeping\n", time, philo->id);
		else if (status == DIED)
			printf("%-6ld %d died\n", time, philo->id);
	}
	safe_mutex_handle(&philo->table->print_mtx, UNLOCK);
}