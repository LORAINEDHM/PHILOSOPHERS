/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduhamel <lduhamel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 13:41:31 by lduhamel          #+#    #+#             */
/*   Updated: 2021/10/01 13:42:11 by lduhamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ph_get_philo_id(int *id_counter, pthread_mutex_t *mutex)
{
	int	id;

	id = 0;
	id = *id_counter;
	pthread_mutex_lock(mutex);
	id = *id_counter;
	(*id_counter)++;
	pthread_mutex_unlock(mutex);
	return (id);
}

int	ph_join_philosophers(t_philo *ph)
{
	int	i;

	i = 0;
	while (i < ph->n_philo)
	{
		if (pthread_join(ph->philo[i], NULL) != 0)
			return (-1);
		i++;
	}
	return (1);
}

int	ph_create_philosophers(t_philo *ph)
{
	int	i;

	i = 0;
	while (i < ph->n_philo)
	{
		if (pthread_create(&ph->philo[i], NULL, function, ph) != 0)
			return (-1);
		i++;
	}
	return (1);
}
