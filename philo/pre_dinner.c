#include "philo.h"

void	set_table(t_dinner *dinner)
{
	dinner->list_of_philos = new_list(dinner);
	pthread_mutex_init(&(dinner->everybody_alive_mutex), NULL);
}
