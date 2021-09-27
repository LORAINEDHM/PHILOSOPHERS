#include "philosophers.h"

unsigned int ph_get_time_today(struct timeval *tv)
{
	unsigned int tv_usec;

	gettimeofday(tv, NULL);
	tv_usec = tv->tv_sec * 1000000 + tv->tv_usec;
	return (tv_usec);
}

// void		check_if_died(t_philo *ph, t_indiv *p)
// {
// 	unsigned int result;
// 	int dead;

// 	dead = 0;
// 	pthread_mutex_lock(&ph->die_mutex);
// 	if (ph->died != 1)
// 	{
// 		//pthread_mutex_lock(&ph->die_mutex);
// 		result = (ph_get_time_today(&p->tv) - p->die_timestamp)/1000;
// 		//printf("result = %u et die_time = %u\n", result, ph->die_time);
// 		if (result >=  (unsigned int)ph->die_time)
// 		{
// 			ph_dead_message(ph, p);
// 			ph->died = 1;
// 		}
// 		//write(1, "hey1\n", 5);
// 		pthread_mutex_unlock(&ph->die_mutex);
// 	}
// 	if (ph->died == 1)
// 		dead = 1;
// 	pthread_mutex_unlock(&ph->die_mutex);
// 	if (dead)
// 		exit(0);
// }