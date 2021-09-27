#include "philosophers.h"

void    ph_take_fork(t_philo *ph, t_indiv *p)
{
	p->l_fork = p->id - 1;
	if (p->id == 1)
		p->l_fork = ph->n_philo;
	ph->fork_id = p->l_fork;
    pthread_mutex_lock(&ph->forks[p->l_fork]);
	ph_write_message(p, ph->start_usec, "has taken a fork\n", &ph->msg_mutex);
	p->r_fork = p->id;
	ph->fork_id = p->r_fork;
	pthread_mutex_lock(&ph->forks[p->r_fork]);
	ph_write_message(p, ph->start_usec, "has taken a fork\n", &ph->msg_mutex);
	ph_write_message(p, ph->start_usec, "is eating\n", &ph->msg_mutex);
	ph->timestamp[p->id - 1] = ph_get_time_today(&ph->tv);
	ph_usleep(p->msg_usec, ph->eat_time * 1000);
	pthread_mutex_unlock(&ph->forks[p->r_fork]);
	pthread_mutex_unlock(&ph->forks[p->l_fork]);
	ph_sleeping(ph, p);
}
