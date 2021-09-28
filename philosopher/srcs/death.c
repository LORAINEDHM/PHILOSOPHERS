#include "philosophers.h"

int		ph_check_if_died(t_philo *ph, pthread_mutex_t *die_mutex)
{
	unsigned int result;
	unsigned int current;
	int id;

	id = 0;
	pthread_mutex_lock(die_mutex);
	current = ph_get_time_today(&ph->tv);
	while (id < ph->n_philo)
	{	
		if (ph->last_meals[id][1] == 1)
			id++;
		else
		{
			result = (current - ph->last_meals[id][0]) / 1000;
			if (result >=  (unsigned int)ph->die_time)
			{
				ph_dead_message(ph, id + 1);
				return (1);
			}
			id++;
		}
	}
	pthread_mutex_unlock(die_mutex);
	return (0);
}

int 	ph_check_if_ate_n_times(t_philo *ph)
{
	int i;

	i = 0;
	while (i < ph->n_philo)
	{
		if (ph->last_meals[i][1] == 0)
			return (0);
		i++;
	}
	return (1);
}


void ph_check_death(t_philo *ph)
{
	pthread_mutex_t	die_mutex;

	while (1)
	{
		if (ph->n_times != -1)
		{
			if (ph_check_if_ate_n_times(ph))
				return ;
		}
		usleep(500);
		if ((ph->died = ph_check_if_died(ph, &die_mutex)))
			return;
	}
}
