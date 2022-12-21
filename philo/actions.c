#include "philo.h"

enum e_fork {left, right};

static int	had_to_release(enum e_fork fork, t_philo *philo)
{
	if (!dinner_must_end(philo)) // nobody_died
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
	if (dinner_must_end(philo)) // someone_died
		return (0);
	if (fork == left)
		pthread_mutex_lock(&(philo->spaghetti_fork));
	else
		pthread_mutex_lock(&(philo->next->spaghetti_fork));
	dinner_log(philo, FORK);
	return (had_to_release(fork, philo));
}

void	eating_action(t_philo *philo)
{
	if (!grab_fork(left, philo)) // 0 -> exit
		return ;
	if (!grab_fork(right, philo))
		return ;
}
