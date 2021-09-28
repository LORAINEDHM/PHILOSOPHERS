#include "philosophers.h"

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

int main(int ac, char **av)
{
    t_philo ph;
    ph = (t_philo){};
	
	ph.id_counter = 1;
	ph_get_argv(ac, av, &ph);
	if (!(ph_parsing(ac, &ph)))
		return (1);
    if (!(ph_malloc(&ph)))
	{
		write(1, "Error: malloc failed\n", 21);
		return (1);
	}
	ph_init_mutex(&ph);
	ph_get_initial_last_meals(&ph);
	if (!(ph_create_philosophers(&ph)))
		return (ph_handle_error(&ph, "Error: create threads failed\n"));
	ph_check_death(&ph);
	if (!(ph_join_philosophers(&ph)))
		return (ph_handle_error(&ph, "Error: join threads failed\n"));
	ph_free_mallocs(ph.philo, ph.forks, ph.last_meals, ph.n_philo);
	ph_destroy_mutex(&ph);
	return (0);
}