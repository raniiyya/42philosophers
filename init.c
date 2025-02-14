/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:53:28 by rdavurov          #+#    #+#             */
/*   Updated: 2025/02/14 12:25:42 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	data_init(t_table *table)
{
	table->dead = false;
	table->philos = save_malloc(sizeof(t_philo) * table->philo_count);
	table->forks = save_malloc(sizeof(t_fork) * table->philo_count);
}