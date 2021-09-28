#include "philosophers.h"

int	ph_write_message(t_philo *ph, t_indiv *p, char *str)
{
	struct timeval current;

	if (ph->died == 1)
		return (0);
	pthread_mutex_lock(&ph->msg_mutex);
	p->msg_usec = ph_get_time_today(&current);
	// if (ph->died == 1)
	// {
	// 	pthread_mutex_unlock(&ph->msg_mutex);
	// 	return (0);
	// }
	//printf("start 2 = %u\n", ph->start_usec);
	ft_putnbr_fd((p->msg_usec - ph->start_usec)/1000, 1);
	write(1, "ms ", 3);
	ft_putnbr_fd(p->id, 1);
	write(1, " ", 1);
	write(1, str, ft_strlen(str));
	pthread_mutex_unlock(&ph->msg_mutex);
	return (1);
}

void	ph_dead_message(t_philo *ph, int id)
{
	struct timeval current;
	unsigned int current_usec;

	current_usec = ph_get_time_today(&current);
	//msg_usec = ph_get_time_today(&current);
	pthread_mutex_lock(&ph->msg_mutex);
	ft_putnbr_fd((current_usec - ph->start_usec)/1000, 1);
	write(1, "ms ", 3);
	ft_putnbr_fd(id, 1);
	write(1, " died\n", 6);
	pthread_mutex_unlock(&ph->msg_mutex);
}
