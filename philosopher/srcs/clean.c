#include "philosophers.h"

void	ph_free_dtab(unsigned int **tab, int n)
{
	int	i;

	i = 0;
	while (i < n)
		free(tab[i++]);
	free(tab);
}