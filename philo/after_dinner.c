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
		philo = philo->next;
	}
	pthread_join(dinner->starvation_thread, NULL);
}

void	unset_table(t_dinner *dinner)
{
	join_threads(dinner);
	clear_list(dinner);
	pthread_mutex_destroy(&(dinner->everybody_alive_mutex));
	pthread_mutex_destroy(&(dinner->log_mutex));
}
