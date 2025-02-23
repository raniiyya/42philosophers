/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 16:12:58 by rdavurov          #+#    #+#             */
/*   Updated: 2025/02/23 16:49:27 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//accesses and modifies the private data members of a structure

void	set_bool(t_mtx *mtx, bool *dest, bool value)
{
	safe_mutex_handle(mtx, LOCK);
	*dest = value;
	safe_mutex_handle(mtx, UNLOCK);
}

bool	get_bool(t_mtx *mtx, bool *src)
{
	bool	value;

	safe_mutex_handle(mtx, LOCK);
	value = *src;
	safe_mutex_handle(mtx, UNLOCK);
	return (value);
}

long	get_long(t_mtx *mtx, long *src)
{
	long	value;

	safe_mutex_handle(mtx, LOCK);
	value = *src;
	safe_mutex_handle(mtx, UNLOCK);
	return (value);
}

void	set_long(t_mtx *mtx, long *dest, long value)
{
	safe_mutex_handle(mtx, LOCK);
	*dest = value;
	safe_mutex_handle(mtx, UNLOCK);
}

bool	simulation_finished(t_table *table)
{
	return (get_bool(&table->table_mtx, &table->end_time));
}