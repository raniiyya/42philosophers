/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:55:45 by rdavurov          #+#    #+#             */
/*   Updated: 2025/02/23 16:52:17 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*safe_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr == NULL)
		error_exit("Malloc error");
	return (ptr);
}

static void	handle_mutex_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (status == EINVAL && opcode == LOCK || opcode == UNLOCK)
		error_exit("The value specified by mutex is invalid");
	else if (status == EINVAL && opcode == INIT)
		error_exit("The value specified by attr is invalid");
	else if (status == EDEADLK)
		error_exit("A end_timelock would occur \
			if the thread blocked waiting for mutex");
	else if (status == EPERM)
		error_exit("The current thread \
			does not lock on the mutex");
	else if (status == ENOMEM)
		error_exit("The process cannot allocate \
			enough memory to create another mutex");
	else if (status == EBUSY)
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
		error_exit("No thread could be found corresponding \
			to that specified by the given thread ID");
	else if (status == EDEADLK)
		error_exit("A end_timelock was detected or the \
			value of thread specifies the calling thread");
}

void	safe_thread_handle(pthread_t *tread, void *(*foo)(void *), \
									void *data, t_opcode opcode)
{
	if (opcode == CREATE)
		handle_thread_error(pthread_create(tread, NULL, foo, data), opcode);
	else if (opcode == JOIN)
		handle_thread_error(pthread_join(*tread, NULL), opcode);
	else if (opcode == DETACH)
		handle_thread_error(pthread_detach(*tread), opcode);
	else
		error_exit("Wrong opcode for thread handle:"
			"use <CREATE> <JOIN> <DETACH>");
}

void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode)
{
	if (opcode == LOCK)
		handle_mutex_error(pthread_mutex_lock(mutex), opcode);
	else if (opcode == UNLOCK)
		handle_mutex_error(pthread_mutex_unlock(mutex), opcode);
	else if (opcode == INIT)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
	else if (opcode == DESTROY)
		handle_mutex_error(pthread_mutex_destroy(mutex), opcode);
	else
		error_exit("Invalid mutex opcode");
}
