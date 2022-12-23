#include "philo.h"

static void	take_time_to_think(t_philo *philo)
{
	struct timeval	thinking_start;
	long			time_without_eating_ms;
	long			time_now_ms;
	long			time_to_think;

	dinner_log(philo, THINK);
	gettimeofday(&thinking_start, NULL);
	time_now_ms = 0;
	time_to_think = (philo->dinner->time_to_die - philo->dinner->time_to_sleep
			- philo->dinner->time_to_eat) / 2;
	if (time_to_think < 0)
		return ;
	while (time_now_ms < time_to_think)
	{
		usleep(250);
		time_without_eating_ms = get_time_in_ms_since_event(philo->last_meal);
		if (time_without_eating_ms >= philo->dinner->time_to_die)
		{
			dinner_log(philo, DIE);
			set_dinner_must_end(philo);
			return ;
		}
		time_now_ms = get_time_in_ms_since_event(thinking_start);
	}
}

static int	should_die_before_thinking(t_philo *philo)
{
	struct timeval	sleeping_start;
	long			time_without_eating_ms;
	long			time_now_ms;

	gettimeofday(&sleeping_start, NULL);
	time_now_ms = 0;
	while (time_now_ms < philo->dinner->time_to_sleep)
	{
		usleep(250);
		time_without_eating_ms = get_time_in_ms_since_event(philo->last_meal);
		if (time_without_eating_ms >= philo->dinner->time_to_die)
			return (1);
		time_now_ms = get_time_in_ms_since_event(sleeping_start);
	}
	return (0);
}

void	sleeping_action(t_philo *philo)
{
	dinner_log(philo, SLEEP);
	if (should_die_before_thinking(philo))
	{
		dinner_log(philo, DIE);
		set_dinner_must_end(philo);
		return ;
	}
	take_time_to_think(philo);
}
