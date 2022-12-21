#include "philo.h"

static int	is_satisfied(t_philo *philo)
{
	return (philo->meals == philo->dinner->max_meals);
}

int	dinner_must_end(t_philo *philo)
{
	int	dinner_must_end;

	pthread_mutex_lock(&(philo->dinner->everybody_alive_mutex));
	dinner_must_end = !(philo->dinner->everybody_alive);
	pthread_mutex_unlock(&(philo->dinner->everybody_alive_mutex));
	return (dinner_must_end);
}

void	end_dinner(t_philo *philo)
{
	pthread_mutex_lock(&(philo->dinner->everybody_alive_mutex));
	philo->dinner->everybody_alive = 0;
	pthread_mutex_unlock(&(philo->dinner->everybody_alive_mutex));
}

void	*start_routine(void *arg)
{
	t_philo	*philo;

	philo = (struct s_philo *)arg;
	while (philo->dinner->everybody_alive)
	{
		eating_action(philo);
		if (is_satisfied(philo))
			break ;
	}
	return (NULL);
}
