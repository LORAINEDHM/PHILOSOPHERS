#include "philosophers.h"

int    ph_take_fork(t_philo *ph, t_indiv *p)
{

	struct timeval current;
	unsigned int current_usec;

	p->l_fork = p->id - 1;
	if (p->id == 1)
		p->l_fork = ph->n_philo;
	p->fork_id = p->l_fork;
    pthread_mutex_lock(&ph->forks[p->l_fork - 1]);
	ph_write_message(ph, p, "has taken a fork\n");
	// if (!(ph_write_message(ph, p, "has taken a fork")))
	// {
	// 	pthread_mutex_unlock(&ph->forks[p->l_fork - 1]);
	// 	return (0);
	// }
	p->r_fork = p->id;
	p->fork_id = p->r_fork;
	pthread_mutex_lock(&ph->forks[p->r_fork - 1]);
	ph_write_message(ph, p, "has taken a fork\n");
	ph_write_message(ph, p, "is eating\n");
	// if ((!(ph_write_message(ph, p, "has taken a fork"))) ||
	// 	(!(ph_write_message(ph, p, "is eating\n"))))
	// {
	// 	pthread_mutex_unlock(&ph->forks[p->l_fork - 1]);
	// 	pthread_mutex_unlock(&ph->forks[p->r_fork - 1]);
	// 	return (0);
	// }
	ph->timestamp[p->id - 1] = ph_get_time_today(&ph->tv);
	ph_usleep(p->msg_usec, ph->eat_time * 1000);

	current_usec = ph_get_time_today(&current);
	//msg_usec = ph_get_time_today(&current);
//	printf("%u ----- %d finished eating\n", (current_usec - ph->start_usec)/1000, p->id);

	pthread_mutex_unlock(&ph->forks[p->l_fork - 1]);
	pthread_mutex_unlock(&ph->forks[p->r_fork - 1]);
	return (1);
	//ph_sleeping(ph, p);
}
