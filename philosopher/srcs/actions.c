/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduhamel <lduhamel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 14:42:11 by lduhamel          #+#    #+#             */
/*   Updated: 2021/10/01 14:42:12 by lduhamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ph_take_fork(t_philo *ph, t_indiv *p)
{
	p->l_fork = p->id - 1;
	if (p->id == 1)
		p->l_fork = ph->n_philo;
	pthread_mutex_lock(&ph->forks[p->l_fork - 1]);
	if (!(ph_write_message(ph, p, "has taken a fork\n")))
		return (ph_unlock(ph, -1, p->l_fork - 1));
	p->r_fork = p->id;
	pthread_mutex_lock(&ph->forks[p->r_fork - 1]);
	if (!(ph_write_message(ph, p, "has taken a fork\n")))
		return (ph_unlock(ph, p->r_fork - 1, p->l_fork - 1));
	ph->last_meals[p->id - 1][0] = ph_get_time_today(&ph->tv);
	if (!(ph_write_message(ph, p, "is eating\n")))
		return (ph_unlock(ph, p->r_fork - 1, p->l_fork - 1));
	ph->last_meals[p->id - 1][0] = ph_get_time_today(&ph->tv);
	ph_usleep(ph_get_time_today(&ph->tv), ph->eat_time * 1000);
	ph_unlock(ph, p->r_fork - 1, p->l_fork - 1);
	return (1);
}

int	ph_sleeping(t_philo *ph, t_indiv *p)
{
	if (!(ph_write_message(ph, p, "is sleeping\n")))
		return (0);
	ph_usleep(p->msg_usec, ph->sleep_time * 1000);
	return (1);
}

int	ph_thinking(t_philo *ph, t_indiv *p)
{
	if (!(ph_write_message(ph, p, "is thinking\n")))
		return (0);
	return (1);
}
