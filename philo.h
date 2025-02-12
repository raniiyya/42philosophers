/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:30:00 by rdavurov          #+#    #+#             */
/*   Updated: 2025/02/12 08:16:38 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h> // printf
# include <stdlib.h> // malloc free
# include <unistd.h> // write sleep
# include <stdbool.h>
# include <pthread.h> // mutex: init destroy lock unlock
					  // thread: create join detach
# include <sys/time.h> // gettimeofday

typedef pthread_mutex_t t_mtx;

typedef struct s_fork
{
	t_mtx	*fork;
	int		fork_id;
}			t_fork;

typedef struct s_philo
{
	int			id;
	long		meals_count;
	bool		full;
	long		last_meal; // time passed since last meal
	t_fork		*left_fork;
	t_fork		*right_fork;
	pthread_t	thread_id;
}				t_philo;

typedef struct s_table
{
	long	philo_count;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	meals_limit;
	long	start_time; // time when the simulation started
	bool	dead; // if a philosopher died or all are full
	t_fork	*forks;
	t_philo	*philos;
}				t_table;

void	error_exit(const char *msg);

#endif