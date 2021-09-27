#include "philosophers.h"

int		check_if_died(t_philo *ph, pthread_mutex_t *die_mutex)
{
	unsigned int result;
	unsigned int current;
	int id;

	id = 0;
	pthread_mutex_lock(die_mutex);
	current = ph_get_time_today(&ph->tv);
	while (id < ph->n_philo)
	{
		result = (current - ph->timestamp[id]) / 1000;
		if (result >=  (unsigned int)ph->die_time)
		{
			ph_dead_message(ph, id + 1);
			return (1);
		}
		id++;
	}
	pthread_mutex_unlock(die_mutex);
	return (0);
}

int check_death(t_philo *ph)
{
	pthread_mutex_t	die_mutex;
	int dead;

	dead = 0;
	while (dead != 1)
	{
		usleep(500);
		if ((dead = check_if_died(ph, &die_mutex)))
			exit(0);
	}
	return (0);
}
