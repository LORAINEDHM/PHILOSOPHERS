#include "philosophers.h"

int	ph_malloc(t_philo *ph)
{
	int	i;

    if (!(ph->philo = malloc(sizeof(pthread_t) * ph->n_philo)))
		return (0);
	if (!(ph->forks = malloc(sizeof(pthread_mutex_t) * (ph->n_philo))))
	{
		ph_free_mallocs(ph->philo, NULL, NULL, 0);
		return (0);
	}
	if (!(ph->last_meals = malloc(sizeof(unsigned int*) * ph->n_philo)))
	{
		ph_free_mallocs(ph->philo, ph->forks, NULL, 0);
		return (0);
	}
	i = 0;
	while (i < ph->n_philo)
	{
		if (!(ph->last_meals[i] = malloc(sizeof(unsigned int) * 2)))
		{
			ph_free_mallocs(ph->philo, ph->forks, ph->last_meals, i + 1);
			return (0);
		}
		ph->last_meals[i][1] = 0;
		i++;
	}
	return (1);
}

void	ph_init_mutex(t_philo *ph)
{
	int i;

	i = 0;
	while (i < ph->n_philo)
		pthread_mutex_init(&ph->forks[i++], NULL);
	pthread_mutex_init(&ph->id_mutex, NULL);
	pthread_mutex_init(&ph->msg_mutex, NULL);
	pthread_mutex_init(&ph->die_mutex, NULL);
}

void ph_get_initial_last_meals(t_philo *ph)
{
	int	i;
	unsigned int	current;

	i = 0;
	current = ph_get_time_today(&ph->tv);
	while (i < ph->n_philo)
		ph->last_meals[i++][0] = current;
	ph->last_meal = current;
}