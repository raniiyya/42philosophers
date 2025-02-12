/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:55:45 by rdavurov          #+#    #+#             */
/*   Updated: 2025/02/12 14:04:02 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*save_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (NULL == ptr)
		error_exit("Malloc error");
	return (ptr);
}

void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode)
{
	if (LOCK == opcode)
		pthread_mutex_lock(mutex);
	else if (UNLOCK == opcode)
		pthread_mutex_unlock(mutex);
	else if (INIT == opcode)
		pthread_mutex_init(mutex, NULL);
	else if (DESTROY == opcode)
		pthread_mutex_destroy(mutex);
	else
		error_exit("Invalid mutex opcode");
}