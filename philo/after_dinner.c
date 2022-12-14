#include "philo.h"

static void	join_threads(t_dinner *dinner)
{
	int		i;
	t_philo	*philo;

	i = -1;
	philo = dinner->list_of_philos;
	while (++i < dinner->nb_of_philosophers)
	{
		pthread_join(philo->thread, NULL);
		philo = philo->prev;
	}
}

void	unset_table(t_dinner *dinner)
{
	// clear_list();
	join_threads(dinner);
}
