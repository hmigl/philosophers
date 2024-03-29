/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_log.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmigl <hmigl@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 08:06:50 by hmigl             #+#    #+#             */
/*   Updated: 2022/12/26 08:06:56 by hmigl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int	get_time_in_ms_since_event(struct timeval event)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000 + now.tv_usec / 1000) \
			- (event.tv_sec * 1000 + event.tv_usec / 1000));
}

void	dinner_log(t_philo *philo, char *action)
{
	long	ts;

	if (get_dinner_must_end(philo))
		return ;
	pthread_mutex_lock(&(philo->dinner->log_mutex));
	ts = get_time_in_ms_since_event(philo->dinner->elapsed_time_dinner_started);
	printf(OUTPUT_TEMPLATE, ts, philo->id, action);
	pthread_mutex_unlock(&(philo->dinner->log_mutex));
}
