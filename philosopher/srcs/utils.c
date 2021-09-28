#include "philosophers.h"

unsigned int ph_get_time_today(struct timeval *tv)
{
	unsigned int tv_usec;

	gettimeofday(tv, NULL);
	tv_usec = tv->tv_sec * 1000000 + tv->tv_usec;
	return (tv_usec);
}

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

// int	ph_write_error(int error, char *str)
// {
// 	write(1, str, ft_strlen(str));
// 	return (error);
// }

// int ph_handle_error()
// {
// 	if (ph->philo)
// 		free (ph->philo);
// 	if (ph->forks)
// 		free (ph->forks);
// 	if (ph->timestamp)
// 		free()
// 	if (str)
// 		return (ph_write_error(error, str));
// 	return ()
// }
