/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduhamel <lduhamel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 12:51:51 by lduhamel          #+#    #+#             */
/*   Updated: 2021/10/01 14:50:16 by lduhamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ph_check_if_digits(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (!(ft_isdigit(av[i][j])))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	ph_parsing(int ac, char **av, t_philo *ph)
{
	if (ac > 6)
		return (ph_write_error("Error: wrong number of arguments\n"));
	if (!(ph_check_if_digits(ac, av)))
		return (ph_write_error("Error: arguments not valid\n"));
	ph_get_argv(ac, av, ph);
	if (ph->eat_time < 0 || ph->die_time < 0 || ph->sleep_time < 0)
		return (ph_write_error("Error: unvalid times\n"));
	if (ph->n_philo > 200 || ph->n_philo <= 0)
		return (ph_write_error("Error: wrong number of philo\n"));
	if (ac == 6 && ph->n_times < 0)
		return (ph_write_error
			("Error: wrong number of times each philo must eat\n"));
	return (1);
}
