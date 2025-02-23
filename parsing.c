/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 09:18:11 by rdavurov          #+#    #+#             */
/*   Updated: 2025/02/23 16:51:48 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static inline bool	is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

static const char	*valid_input(const char *str)
{
	int			len;
	const char	*number;

	len = 0;
	while (is_space(*str))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
		error_exit("Only positive numbers are allowed!");
	if (!is_digit(*str))
		error_exit("Invalid input");
	number = str;
	while (is_digit(*str++))
		++len;
	if (len > 10)
		error_exit("Number is too big");
	return (number);
}

static long		ft_atol(const char *str)
{
	long	num;

	num = 0;
	str = valid_input(str);
	while (is_digit(*str))
		num = (num * 10) + (*str++ - '0');
	if (num > 2147483647)
		error_exit("Number is too big");
	return (num);
}	

void	parse_input(t_table *table, char **av)
{
	table->philo_count = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]) * 1e3;
	table->time_to_eat = ft_atol(av[3]) * 1e3;
	table->time_to_sleep = ft_atol(av[4]) * 1e3;
	if (table->time_to_die < 6e4 || table->time_to_eat < 6e4 || table->time_to_sleep < 6e4)
		error_exit("Use timestamps bigger than 60ms");
	if (av[5])
		table->meals_limit = ft_atol(av[5]);
	else
		table->meals_limit = -1;
}