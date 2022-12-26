/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_death.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmigl <hmigl@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 08:06:51 by hmigl             #+#    #+#             */
/*   Updated: 2022/12/26 08:06:56 by hmigl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	has_everyone_eaten(t_philo *philo)
{
	pthread_mutex_lock(&(philo->dinner->satisfaction_mutex));
	if (philo->dinner->satisfied_philos
		== philo->dinner->nb_of_philosophers)
		return (1);
	return (0);
}

static int	is_starving(t_philo *philo)
{
	pthread_mutex_lock(&(philo->last_meal_mutex));
	if (!(get_time_in_ms_since_event(philo->last_meal)
			>= philo->dinner->time_to_die))
		return (0);
	dinner_log(philo, DIE);
	set_dinner_must_end(philo);
	return (1);
}

static void	*unlock_locks(int satisaction_lock, int last_meal_lock, t_philo *p)
{
	if (satisaction_lock)
		pthread_mutex_unlock(&(p->dinner->satisfaction_mutex));
	if (last_meal_lock)
		pthread_mutex_unlock(&(p->last_meal_mutex));
	return (NULL);
}

void	*death_routine(void *arg)
{
	t_philo	*philo;
	int		satisaction_mutex;
	int		last_meal_mutex;

	satisaction_mutex = 0;
	last_meal_mutex = 0;
	philo = (struct s_philo *)arg;
	while (!get_dinner_must_end(philo))
	{
		if (has_everyone_eaten(philo))
		{
			satisaction_mutex = 1;
			break ;
		}
		pthread_mutex_unlock(&(philo->dinner->satisfaction_mutex));
		if (is_starving(philo))
		{
			last_meal_mutex = 1;
			break ;
		}
		pthread_mutex_unlock(&(philo->last_meal_mutex));
		philo = philo->next;
		usleep(250);
	}
	return (unlock_locks(satisaction_mutex, last_meal_mutex, philo));
}
