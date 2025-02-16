/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 16:58:38 by rdavurov          #+#    #+#             */
/*   Updated: 2025/02/16 19:11:43 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//spinlock to sync philos

void	wait_all_threads(t_table *table)
{
	while (!get_bool(&table->table_mtx, &table->all_threads_ready))
		;
}