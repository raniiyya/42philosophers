/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:55:45 by rdavurov          #+#    #+#             */
/*   Updated: 2025/02/14 12:20:33 by codespace        ###   ########.fr       */
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

static void	handle_mutex_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (EINVAL == status && LOCK == opcode || UNLOCK == opcode)
		error_exit("The value specified by mutex is invalid");
	else if (EINVAL == status && INIT == opcode)
		error_exit("The value specified by attr is invalid");
	else if (EDEADLK == status)
		error_exit("A deadlock would occur if the thread blocked waiting for mutex");
	else if (EPERM == status)
		error_exit("The current thread does not lock on the mutex");
	else if (ENOMEM == status)
		error_exit("The process cannot allocate enough memory to create another mutex");
	else if (EBUSY == status)
		error_exit("The mutex is locked");
}

void	safe_thread_handle(pthread_t *tread, void *(*foo)(void *), void *data, t_opcode opcode)
{
	if (CREATE == opcode)
		handle_thread_error(pthread_create(tread, NULL, foo, data), opcode);
	else if (JOIN == opcode)
		handle_thread_error(pthread_join(*tread, NULL), opcode);
	else if (DETACH == opcode)
		handle_thread_error(pthread_detach(*tread), opcode);
	else
		error_exit("Wrong opcode for thread handle:"
		"use <CREATE> <JOIN> <DETACH>");
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