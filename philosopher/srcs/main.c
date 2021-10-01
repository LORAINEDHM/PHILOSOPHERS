/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduhamel <lduhamel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 13:59:45 by lduhamel          #+#    #+#             */
/*   Updated: 2021/10/01 14:43:19 by lduhamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ph_one_philo(t_philo *ph, t_indiv *p)
{
	pthread_mutex_lock(&ph->forks[0]);
	if (!(ph_write_message(ph, p, "has taken a fork\n")))
	{
		pthread_mutex_unlock(&ph->forks[0]);
		return (0);
	}
	if (ph->died == 1)
	{
		pthread_mutex_unlock(&ph->forks[0]);
		return (0);
	}
	return (1);
}

int	ph_multiple_philo(t_philo *ph, t_indiv *p)
{
	int		counter;

	counter = 0;
	while (1)
	{
		if (ph->n_times != -1)
		{
			if (counter >= ph->n_times)
			{
				ph->last_meals[p->id - 1][1] = 1;
				break ;
			}
		}
		if (counter != 0)
			if (!(ph_thinking(ph, p)))
				return (0);
		if ((!(ph_take_fork(ph, p)))
			|| (!(ph_sleeping(ph, p))))
			return (0);
		counter++;
	}
	return (1);
}

void	ph_odd_waiting(int id, int eat_time)
{	
	if (id % 2 != 0)
		usleep((eat_time / 2) * 1000);
}

void	*function(void	*arg)
{
	t_philo	*ph;
	t_indiv	p;

	p.id = 0;
	ph = (t_philo *)arg;
	p.id = ph_get_philo_id(&ph->id_counter, &ph->id_mutex);
	if (ph->n_philo == 1)
		ph_one_philo(ph, &p);
	else
	{
		ph_odd_waiting(p.id, ph->eat_time);
		ph_multiple_philo(ph, &p);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_philo	ph;

	ph = (t_philo){};
	ph.id_counter = 1;
	if (!(ph_parsing(ac, av, &ph)))
		return (1);
	if (!(ph_malloc(&ph)))
	{
		write(1, "Error: malloc failed\n", 21);
		return (1);
	}
	ph_init_mutex(&ph);
	ph_get_initial_last_meals(&ph);
	if (!(ph_create_philosophers(&ph)))
		return (ph_handle_error(&ph, "Error: create threads failed\n"));
	ph_check_death(&ph);
	if (!(ph_join_philosophers(&ph)))
		return (ph_handle_error(&ph, "Error: join threads failed\n"));
	ph_free_mallocs(ph.philo, ph.forks, ph.last_meals, ph.n_philo);
	ph_destroy_mutex(&ph);
	return (0);
}
