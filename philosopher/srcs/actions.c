#include "philosophers.h"


int	ph_one_philo(t_philo *ph, t_indiv *p)
{
	pthread_mutex_lock(&ph->forks[0]);
	if (!(ph_write_message(ph, p, "has taken a fork\n")))
	{
		pthread_mutex_unlock(&ph->forks[0]);
		return (0);
	}
	if (ph->died == 1)
	{
		pthread_mutex_unlock(&ph->forks[0]);
		return(0);
	}
	return (1);
}



int    ph_take_fork(t_philo *ph, t_indiv *p)
{
	p->l_fork = p->id - 1;
	if (p->id == 1)
		p->l_fork = ph->n_philo;
    pthread_mutex_lock(&ph->forks[p->l_fork - 1]);
	if (!(ph_write_message(ph, p, "has taken a fork\n")))
	{
		pthread_mutex_unlock(&ph->forks[p->l_fork - 1]);
		return (0);
	}
	p->r_fork = p->id;
	pthread_mutex_lock(&ph->forks[p->r_fork - 1]);
	if ((!(ph_write_message(ph, p, "has taken a fork\n"))) ||
		(!(ph_write_message(ph, p, "is eating\n"))))
	{
		pthread_mutex_unlock(&ph->forks[p->l_fork - 1]);
		pthread_mutex_unlock(&ph->forks[p->r_fork - 1]);
		return (0);
	}
	ph->last_meals[p->id - 1][0] = ph_get_time_today(&ph->tv);
	ph_usleep(p->msg_usec, ph->eat_time * 1000);
	pthread_mutex_unlock(&ph->forks[p->l_fork - 1]);
	pthread_mutex_unlock(&ph->forks[p->r_fork - 1]);
	return (1);
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