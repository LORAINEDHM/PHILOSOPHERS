#include "philosophers.h"

void	ph_usleep(unsigned int start_usec, unsigned int time)
{
	//struct timeval start;
	struct timeval current;
	//unsigned int start_usec;
	unsigned int current_usec;

	//start_usec = ph_get_time_today(&start);
	current_usec = ph_get_time_today(&current);
	while (current_usec < (start_usec + (long)time))
	{
		usleep(500);
		current_usec = ph_get_time_today(&current);
	}
	if (current_usec != (start_usec + (long)time))
		usleep(500);
}


void	ph_sleeping(t_philo *ph, t_indiv *p)
{
	ph_write_message(p, ph->start_usec, "is sleeping\n", &ph->msg_mutex);
	ph_usleep(p->msg_usec, ph->sleep_time * 1000);
}

void	ph_thinking(t_philo *ph, t_indiv *p)
{
	ph_write_message(p, ph->start_usec, "is thinking\n", &ph->msg_mutex);
}