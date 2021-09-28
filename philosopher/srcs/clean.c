#include "philosophers.h"

void	ph_free_dtab(unsigned int **tab, int n)
{
	int	i;

	i = 0;
	while (i < n)
		free(tab[i++]);
	free(tab);
}

int	ph_free_mallocs(pthread_t *philo, pthread_mutex_t *forks, unsigned int **last_meals, int n)
{
	if (philo)
		free(philo);
	if (forks)
		free(forks);
	if (last_meals)
		ph_free_dtab(last_meals, n);
	return (0);
}

void	ph_destroy_mutex(t_philo *ph)
{
	pthread_mutex_destroy(&ph->id_mutex);
	pthread_mutex_destroy(&ph->msg_mutex);
	pthread_mutex_destroy(&ph->die_mutex);
}

int	ph_handle_error(t_philo *ph, char *str)
{
	ph_free_mallocs(ph->philo, ph->forks, ph->last_meals, ph->n_philo);
	ph_destroy_mutex(ph);
	write (1, str, ft_strlen(str));
	return (1);
}

int ph_write_error(char *str)
{
	write(1, str, ft_strlen(str));
	return (0);
}
