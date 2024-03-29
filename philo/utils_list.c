/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmigl <hmigl@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 08:06:51 by hmigl             #+#    #+#             */
/*   Updated: 2022/12/26 08:06:56 by hmigl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_philo	*new_philo(int id, t_dinner *dinner)
{
	t_philo	*philo;

	philo = (struct s_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = id + 1;
	philo->prev = philo;
	philo->next = philo;
	philo->meals = 0;
	philo->dinner = dinner;
	philo->last_meal = dinner->elapsed_time_dinner_started;
	pthread_mutex_init(&(philo->spaghetti_fork), NULL);
	pthread_mutex_init(&(philo->last_meal_mutex), NULL);
	return (philo);
}

static void	lst_add_end(t_philo **head, t_philo *philo)
{
	t_philo	*last;

	if (*head == NULL)
	{
		*head = philo;
		return ;
	}
	last = (*head)->prev;
	philo->next = *head;
	philo->prev = last;
	(*head)->prev = philo;
	last->next = philo;
}

t_philo	*new_list(t_dinner *dinner)
{
	int		id;
	t_philo	*list_of_philos;

	list_of_philos = NULL;
	id = -1;
	while (++id < dinner->nb_of_philosophers)
		lst_add_end(&list_of_philos, new_philo(id, dinner));
	return (list_of_philos);
}

void	clear_list(t_dinner *dinner)
{
	int		i;
	t_philo	*tmp;

	i = -1;
	while (++i < dinner->nb_of_philosophers)
	{
		tmp = dinner->list_of_philos;
		dinner->list_of_philos = dinner->list_of_philos->next;
		pthread_mutex_destroy(&(tmp->spaghetti_fork));
		pthread_mutex_destroy(&(tmp->last_meal_mutex));
		free(tmp);
		tmp = NULL;
	}
}
