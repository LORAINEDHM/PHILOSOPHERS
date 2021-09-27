#include "philosophers.h"

// int	ph_write_message(int timestamp, int id, char *str, pthread_mutex_t *mutex)
// int	ph_write_message(t_philo *ph, t_indiv *p, char *str, pthread_mutex_t *mutex)
// {
// 	struct timeval current;
// 	//unsigned int current_usec;

// 	ph->msg_usec = ph_get_time_today(&current);
// 	check_if_died(ph, p);
// 	pthread_mutex_lock(mutex);
// 	ft_putnbr_fd((ph->msg_usec - ph->start_usec)/1000, 1);
// 	write(1, "ms ", 3);
// 	ft_putnbr_fd(p->id, 1);
// 	write(1, " ", 1);
// 	write(1, str, ft_strlen(str));
// 	pthread_mutex_unlock(mutex);
// 	return (1);
// }

int	ph_write_message(t_indiv *p, int start_usec, char *str, pthread_mutex_t *mutex)
{
	struct timeval current;
	//unsigned int current_usec;

	p->msg_usec = ph_get_time_today(&current);
	//printf("msg_usec = %u\n", p->msg_usec);
	pthread_mutex_lock(mutex);
	ft_putnbr_fd((p->msg_usec - start_usec)/1000, 1);
	write(1, "ms ", 3);
	ft_putnbr_fd(p->id, 1);
	write(1, " ", 1);
	write(1, str, ft_strlen(str));
	pthread_mutex_unlock(mutex);
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
