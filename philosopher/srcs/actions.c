#include "philosophers.h"

void	ph_usleep(unsigned int start_usec, unsigned int time)
{
	struct timeval current;
	unsigned int current_usec;

	current_usec = ph_get_time_today(&current);
	while (current_usec < (start_usec + (long)time))
	{
		usleep(100);
		current_usec = ph_get_time_today(&current);
	}
	if (current_usec != (start_usec + (long)time))
		usleep(100);
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