#include "philosophers.h"

void	ph_get_argv(int ac, char **av, t_philo *ph)
{
	ph->n_philo = ft_atoi(av[1]);
    ph->die_time = ft_atoi(av[2]);
    ph->eat_time = ft_atoi(av[3]);
    ph->sleep_time = ft_atoi(av[4]);
	if (ac == 6)
		ph->n_times = ft_atoi(av[5]);
	else
		ph->n_times = -1;
}


int    ph_init(t_philo *ph)
{
	int i;

    if (!(ph->philo = malloc(sizeof(pthread_t) * ph->n_philo)))
		return (0);
	pthread_mutex_init(&ph->id_mutex, NULL);
	pthread_mutex_init(&ph->msg_mutex, NULL);
	pthread_mutex_init(&ph->die_mutex, NULL);
	if (!(ph->forks = malloc(sizeof(pthread_mutex_t) * (ph->n_philo))))
		return (0);
	i = 0;
	while (i < ph->n_philo)
	{
		pthread_mutex_init(&ph->forks[i++], NULL);
	}
	if (!(ph->last_meals = malloc(sizeof(unsigned int*) * ph->n_philo)))
		return (0);
	i = 0;
	while (i < ph->n_philo)
	{
		if (!(ph->last_meals[i] = malloc(sizeof(unsigned int) * 2)))
			return (0);
		ph->last_meals[i][1] = 0;
		i++;
	}
	ph->died = 0;
	ph->ate_n_times = 0;
	return (1);
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
	if (ph->n_philo == 1)
		ph_one_philo(ph, &p);
	else
	{
		ph_odd_waiting(p.id, ph->eat_time);
		while (1)
		{
	//	printf("\n\n\n COUNTER = %d   |   p.id = %d\n\n", counter, p.id);
			if (ph->n_times != -1)
				{
					if (counter >= ph->n_times)
					{
						ph->last_meals[p.id - 1][1] = 1;
						break;
					}
				}
			if (counter != 0)
				if (!(ph_thinking(ph, &p)))
					return (int*)(1);
			if ((!(ph_take_fork(ph, &p))) ||
				(!(ph_sleeping(ph, &p))))
				return (int*)(1);
			counter++;
		}
	}
	return (0);
}

void ph_get_initial_last_meals(t_philo *ph)
{
	int	i;
	unsigned int current;

	i = 0;
	current = ph_get_time_today(&ph->tv);
	while (i < ph->n_philo)
		ph->last_meals[i++][0] = current;
	ph->last_meal = current;
}

int main(int ac, char **av)
{
    t_philo ph;
    ph = (t_philo){};
	
	ph.id_counter = 1;
	ph_get_argv(ac, av, &ph);
    if (!(ph_init(&ph)))
		return(1);
	ph_get_initial_last_meals(&ph);
	if (!(ph_create_philosophers(&ph)))
		return (1);
	ph_check_death(&ph);
	if (!(ph_join_philosophers(&ph)))
		return (1);
	pthread_mutex_destroy(&ph.id_mutex);
	pthread_mutex_destroy(&ph.msg_mutex);
	pthread_mutex_destroy(&ph.die_mutex);
	return (0);
}