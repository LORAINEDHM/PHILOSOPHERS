#include "philosophers.h"

int ph_parsing(int ac, t_philo *ph)
{
	(void)ph;
	if (ac > 6)
		return (ph_write_error("Error: wrong number of arguments\n"));
	return (1);
}