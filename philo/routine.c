#include "philo.h"

static int	is_satisfied(t_philo *philo)
{
	return (philo->meals == philo->dinner->max_meals);
}

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

void	*start_routine(void *arg)
{
	t_philo	*philo;

	philo = (struct s_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(100);
	while (philo->dinner->everybody_alive)
	{
		eating_action(philo);
		if (is_satisfied(philo))
			break ;
		sleeping_action(philo);
	}
	return (NULL);
}

void	*death_routine(void *arg)
{
	t_philo	*philo;

	philo = (struct s_philo *)arg;
	while (philo->dinner->everybody_alive)
	{
		if (get_time_in_ms_since_event(philo->last_meal)
			>= philo->dinner->time_to_die)
		{
			dinner_log(philo, DIE);
			set_dinner_must_end(philo);
			break ;
		}
		philo = philo->next;
		usleep(250);
	}
	return (NULL);
}
