/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:55:45 by rdavurov          #+#    #+#             */
/*   Updated: 2025/02/17 12:31:50 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*safe_malloc(size_t size)
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

static void	handle_thread_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (status == EAGAIN)
		error_exit("No resources to create another thread");
	else if (status == EPERM)
		error_exit("The caller does not have the permission");
	else if (status == EINVAL && opcode == CREATE)
		error_exit("The value specified by attr is invalid");
	else if (status == EINVAL && (opcode == JOIN || opcode == DETACH))
		error_exit("The thread is not joinable");
	else if (status == ESRCH)
		error_exit("No thread could be found corresponding to that specified by the given thread ID");
	else if (status == EDEADLK)
		error_exit("A deadlock was detected or the value of thread specifies the calling thread");
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
		handle_mutex_error(pthread_mutex_lock(mutex), opcode);
	else if (UNLOCK == opcode)
		handle_mutex_error(pthread_mutex_unlock(mutex), opcode);
	else if (INIT == opcode)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
	else if (DESTROY == opcode)
		handle_mutex_error(pthread_mutex_destroy(mutex), opcode);
	else
		error_exit("Invalid mutex opcode");
}