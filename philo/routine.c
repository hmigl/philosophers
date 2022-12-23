#include "philo.h"

int	get_dinner_must_end(t_philo *philo)
{
	int	dinner_must_end;

	pthread_mutex_lock(&(philo->dinner->everybody_alive_mutex));
	dinner_must_end = !(philo->dinner->everybody_alive);
	pthread_mutex_unlock(&(philo->dinner->everybody_alive_mutex));
	return (dinner_must_end);
}

void	set_dinner_must_end(t_philo *philo)
{
	pthread_mutex_lock(&(philo->dinner->everybody_alive_mutex));
	philo->dinner->everybody_alive = 0;
	pthread_mutex_unlock(&(philo->dinner->everybody_alive_mutex));
}

static void	*dine_alone(t_philo *philo)
{
	pthread_mutex_lock(&(philo->spaghetti_fork));
	dinner_log(philo, FORK);
	pthread_mutex_unlock(&(philo->spaghetti_fork));
	return (NULL);
}

void	*start_routine(void *arg)
{
	t_philo	*philo;

	philo = (struct s_philo *)arg;
	if (philo->dinner->nb_of_philosophers == 1)
		return (dine_alone(philo));
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!get_dinner_must_end(philo))
	{
		eating_action(philo);
		if (philo->meals == philo->dinner->max_meals)
			break ;
		sleeping_action(philo);
	}
	pthread_mutex_lock(&(philo->dinner->satisfaction_mutex));
	philo->dinner->nb_of_philos_who_already_ate++;
	pthread_mutex_unlock(&(philo->dinner->satisfaction_mutex));
	return (NULL);
}
