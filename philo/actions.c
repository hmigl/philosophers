#include "philo.h"

enum e_fork {left, right};

static int	had_to_release(enum e_fork fork, t_philo *philo)
{
	if (!dinner_must_end(philo))
		return (1);
	if (fork == left)
		pthread_mutex_unlock(&(philo->spaghetti_fork));
	else
	{
		pthread_mutex_unlock(&(philo->spaghetti_fork));
		pthread_mutex_unlock(&(philo->next->spaghetti_fork));
	}
	return (0);
}

static int	grab_fork(enum e_fork fork, t_philo *philo)
{
	if (dinner_must_end(philo))
		return (0);
	if (fork == left)
		pthread_mutex_lock(&(philo->spaghetti_fork));
	else
		pthread_mutex_lock(&(philo->next->spaghetti_fork));
	dinner_log(philo, FORK);
	return (had_to_release(fork, philo));
}

static void	die_using_ceil_timestamp(t_philo *philo)
{
	size_t	ceil_timestamp;

	ceil_timestamp = philo->dinner->time_to_die * 1000;
	usleep(ceil_timestamp);
	end_dinner(philo);
	dinner_log(philo, DIE);
}

void	eating_action(t_philo *philo)
{
	if (!grab_fork(left, philo))
		return ;
	if (!grab_fork(right, philo))
		return ;
	if (philo->dinner->time_to_eat > philo->dinner->time_to_die)
		return (die_using_ceil_timestamp(philo));
}
