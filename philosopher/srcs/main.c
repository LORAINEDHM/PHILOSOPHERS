#include "philosophers.h"


void    ph_init(int ac, char **av, t_philo *ph)
{
	int i;

	i = 0;
    ph->n_philo = ft_atoi(av[1]);
    ph->die_time = ft_atoi(av[2]);
    ph->eat_time = ft_atoi(av[3]);
    ph->sleep_time = ft_atoi(av[4]);
	if (ac == 6)
		ph->n_times = ft_atoi(av[5]);
	else
		ph->n_times = -1;
    ph->philo = malloc(sizeof(pthread_t) * ph->n_philo);
	pthread_mutex_init(&ph->id_mutex, NULL);
	pthread_mutex_init(&ph->msg_mutex, NULL);
	pthread_mutex_init(&ph->die_mutex, NULL);
	ph->forks = malloc(sizeof(pthread_mutex_t));
	while (i < ph->n_philo + 1)
	{
		pthread_mutex_init(&ph->forks[i++], NULL);
	}
	ph->timestamp = malloc(sizeof(unsigned int) * ph->n_philo);
}

void ph_odd_waiting(int id, int eat_time)
{
	if (id % 2 != 0)
		usleep((eat_time / 2) * 1000);
}

void* function(void* arg)
{
	t_philo	*ph;
	t_indiv	p;
	int	counter;

	counter = 0;
	p.id = 0;
	ph = (t_philo*)arg;
	p.id = ph_get_philo_id(&ph->id_counter, &ph->id_mutex);
	while (1)
	{
		//printf("\n\n\n COUNTER = %d\n\n", counter);
		if (ph->n_times != -1)
			{
				if (counter >= ph->n_times)
					break;
			}
		if (counter == 0)
			ph_odd_waiting(p.id, ph->eat_time);
		if (counter != 0)
			ph_thinking(ph, &p);
		ph_take_fork(ph, &p);
		counter++;
	}
	return (0);
}

void ph_get_initial_timestamp(t_philo *ph)
{
	int	i;
	unsigned int current;

	i = 0;
	current = ph_get_time_today(&ph->tv);
	while (i < ph->n_philo)
		ph->timestamp[i++] = current;
	ph->start_usec = ph_get_time_today(&ph->tv);
}

int main(int ac, char **av)
{
    // (void) ac;
    // t_philo *ph;
	// ph = malloc(sizeof(t_philo));
    // ph = &((t_philo){});
	// ph->id_counter = 0;
    // ph_init(av, ph);
	// if (!(ph_create_philosophers(ph)))
	// 	return (0);
	// printf("hello\n");
	// return (1);

	(void) ac;
    t_philo ph;
    ph = (t_philo){};
	
	ph.id_counter = 1;
	ph.n_times = 1;
    ph_init(ac, av, &ph);
	ph_get_initial_timestamp(&ph);
	if (!(ph_create_philosophers(&ph)))
		return (0);
	if (!(check_death(&ph)))
		exit(0);
	if (!(ph_join_philosophers(&ph)))
		return (0);
	pthread_mutex_destroy(&ph.id_mutex);
	pthread_mutex_destroy(&ph.msg_mutex);
	pthread_mutex_destroy(&ph.die_mutex);
	return (1);
}