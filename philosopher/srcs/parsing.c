#include "philosophers.h"

int ph_check_if_digits(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (!(ft_isdigit(av[i][j])))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}



int ph_parsing(int ac, char **av, t_philo *ph)
{
	(void)ph;
	if (ac > 6)
		return (ph_write_error("Error: wrong number of arguments\n"));
	if (!(ph_check_if_digits(ac, av)))
		return (ph_write_error("Error: arguments not valid\n"));
	ph_get_argv(ac, av, ph);
	if (ph->n_philo > 200 || ph->n_philo <= 0)
		return (ph_write_error("Error: wrong number of philo\n"));
	if (ac == 6 && ph->n_times < 0)
		return (ph_write_error("Error: wrong number of times each philo must eat\n"));
	//printf("eat_time = %d  |  die_time = %d  |  sleep_time = %d   | n_time = %d\n", ph->eat_time, ph->die_time, ph->sleep_time, ph->n_times);
	return (1);
}