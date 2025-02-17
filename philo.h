/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:30:00 by rdavurov          #+#    #+#             */
/*   Updated: 2025/02/17 12:42:09 by codespace        ###   ########.fr       */
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
# include <errno.h> // error handling
# define DEBUG_MODE 0

typedef enum	e_status
{
	THINKING,
	EATING,
	SLEEPING,
	TAKE_FIRS_FORK,
	TAKE_SECOND_FORK,
	DIED,
}		t_philo_status;

typedef enum	e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}		t_opcode;

typedef	enum	e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}		t_time_code;

typedef pthread_mutex_t t_mtx;

typedef struct s_table t_table;

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
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id;
	t_mtx		*philo_mtx;
	t_table		*table;
}				t_philo;

typedef struct s_table
{
	long		philo_count;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		meals_limit;
	long		start_time; // time when the simulation started
	long		threads_running_num;
	bool		dead; // if a philosopher died or all are full
	bool		all_threads_ready;
	pthread_t	monitor;
	t_mtx		*table_mtx;
	t_mtx		*print_mtx;
	t_fork		*forks;
	t_philo		*philos;
}				t_table;

//dinner.c
void	thinking(t_philo *philo, bool pre_simulation);
void	*lone_philo(void *arg);
void	*dinner_simulation(void *data);
void	dinner_start(t_table *table);

//getters_setters.c
void	set_bool(t_mtx *mtx, bool *dest, bool value);
void	set_long(t_mtx *mtx, long *dest, long value);
long	get_long(t_mtx *mtx, long *src);
bool	get_bool(t_mtx *mtx, bool *src);
bool	simulation_finished(t_table *table);

//init.c
void	data_init(t_table *table);

//monitor.c
void	*monitor_dinner(void *data);

//parsing.c
void	parse_input(t_table *table, char **av);

//safe_functions.c
void	*safe_malloc(size_t size);
void	safe_thread_handle(pthread_t *tread, void *(*foo)(void *), void *data, t_opcode opcode);
void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode);

//sync_utils.c
void	wait_all_threads(t_table *table);
bool	all_threads_running(t_mtx *mtx, long *threads, long philo_num);
void	increase_long(t_mtx *mtx, long *var, long value);
void	de_sync_philos(t_philo *philo);

//utils.c
long	gettime(t_time_code time_code);
void	precise_usleep(long usec, t_table *table);
void	clean(t_table *table);
void	error_exit(const char *msg);

//write.c
void	write_status(t_philo_status status, t_philo *philo, bool debug);

#endif