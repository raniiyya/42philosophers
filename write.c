/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 17:35:59 by rdavurov          #+#    #+#             */
/*   Updated: 2025/02/17 12:44:53 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	write_status_debug(t_philo_status status, t_philo *philo, long time)
{
	if (TAKE_FIRS_FORK == status)
		printf("%-6ld %d has taken the first fork\n", time, philo->id);
	else if (TAKE_SECOND_FORK == status)
		printf("%-6ld %d has taken the second fork\n", time, philo->id);
	else if (EATING == status)
		printf("%-6ld %d is eating\n", time, philo->id);
	else if (THINKING == status)
		printf("%-6ld %d is thinking\n", time, philo->id);
	else if (SLEEPING == status)
		printf("%-6ld %d is sleeping\n", time, philo->id);
	else if (DIED == status)
		printf("%-6ld %d died\n", time, philo->id);
}

void	write_status(t_philo_status status, t_philo *philo, bool debug)
{
	long	time;

	time = gettime(MILLISECOND) - philo->table->start_time;
	if (philo->full)
		return ;
	safe_mutex_handle(philo->table->table_mtx, LOCK);
	if (debug)
		write_status_debug(status, philo, time);
	else
	{
		if ((TAKE_FIRS_FORK == status || TAKE_SECOND_FORK == status)
			&& !simulation_finished(philo->table))
			printf("%-6ld %d has taken a fork\n", time, philo->id);
		else if (EATING == status && !simulation_finished(philo->table))
			printf("%-6ld %d is eating\n", time, philo->id);
		else if (THINKING == status && !simulation_finished(philo->table))
			printf("%-6ld %d is thinking\n", time, philo->id);
		else if (SLEEPING == status && !simulation_finished(philo->table))
			printf("%-6ld %d is sleeping\n", time, philo->id);
		else if (DIED == status)
			printf("%-6ld %d died\n", time, philo->id);
	}
	safe_mutex_handle(philo->table->print_mtx, UNLOCK);
	
}