#include "philo.h"

void	dinner_log(t_philo *philo, char *action)
{
	if (dinner_must_end(philo))
		return ;
	pthread_mutex_lock(&(philo->dinner->log_mutex));
	printf(OUTPUT_TEMPLATE, 42, philo->id, action);
	pthread_mutex_unlock(&(philo->dinner->log_mutex));
}
