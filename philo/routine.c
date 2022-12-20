#include "philo.h"

static int	still_not_satisfied(t_philo *philo)
{
	return (philo->meals < philo->dinner->max_meals);
}

void	*start_routine(void *arg)
{
	t_philo	*philo;
	int		eating_nonstop;

	philo = (struct s_philo *)arg;
	eating_nonstop = philo->dinner->max_meals < 0;
	while (eating_nonstop || (!eating_nonstop && still_not_satisfied(philo)))
	{
		;
	}
	return (NULL);
}
