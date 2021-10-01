/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduhamel <lduhamel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 13:55:19 by lduhamel          #+#    #+#             */
/*   Updated: 2021/10/01 14:37:09 by lduhamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
	{
		i++;
	}
	return (i);
}

unsigned int	ph_get_time_today(struct timeval *tv)
{
	unsigned int	tv_usec;

	gettimeofday(tv, NULL);
	tv_usec = tv->tv_sec * 1000000 + tv->tv_usec;
	return (tv_usec);
}

void	ph_usleep(unsigned int start_usec, unsigned int time)
{
	struct timeval	current;
	unsigned int	current_usec;

	current_usec = ph_get_time_today(&current);
	while (current_usec < (start_usec + (long)time))
	{
		usleep(100);
		current_usec = ph_get_time_today(&current);
	}
	if (current_usec != (start_usec + (long)time))
		usleep(100);
}

int	ph_unlock(t_philo *ph, int fork_r, int fork_l)
{
	if (fork_l >= 0)
		pthread_mutex_unlock(&ph->forks[fork_l]);
	if (fork_r >= 0)
		pthread_mutex_unlock(&ph->forks[fork_r]);
	return (0);
}
