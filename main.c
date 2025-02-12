/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:25:26 by rdavurov          #+#    #+#             */
/*   Updated: 2025/02/12 08:17:27 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		main(int ac, char **av)
{
	t_table	table;
	
	if (5 == ac || 6 == ac)
	{
		parse_input(&table, av); //errors checking, filling table
		data_init(&table); // creating the thing
		dinner_start(&table); // starting the simulation
		clean(&table); // freeing the memory, philo is full or dead
	}
	else
		error_exit("Wrong input");	
}