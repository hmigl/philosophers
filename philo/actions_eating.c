#include "philo.h"

enum e_fork {left, right};

static int	had_to_release(enum e_fork fork, t_philo *philo)
{
	if (!get_dinner_must_end(philo))
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
	if (get_dinner_must_end(philo))
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
	long	ceil_timestamp;

	ceil_timestamp = philo->dinner->time_to_die * 1000;
	usleep(ceil_timestamp);
	dinner_log(philo, DIE);
	set_dinner_must_end(philo);
}

static void	eat(t_philo *philo)
{
	dinner_log(philo, EAT);
	philo->meals++;
	gettimeofday(&(philo->last_meal), NULL);
	usleep(philo->dinner->time_to_eat * 1000);
}

void	eating_action(t_philo *philo)
{
	if (get_time_in_ms_since_event(philo->last_meal) \
			>= philo->dinner->time_to_die)
	{
		dinner_log(philo, DIE);
		set_dinner_must_end(philo);
		return ;
	}
	if (!grab_fork(left, philo))
		return ;
	if (!grab_fork(right, philo))
		return ;
	if (philo->dinner->time_to_eat > philo->dinner->time_to_die)
		die_using_ceil_timestamp(philo);
	else
		eat(philo);
	pthread_mutex_unlock(&(philo->spaghetti_fork));
	pthread_mutex_unlock(&(philo->next->spaghetti_fork));
}
