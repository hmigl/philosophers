#include "philo.h"

static t_philo	*lst_new(int id, t_dinner *dinner)
{
	t_philo	*philo;

	philo = (struct s_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = id + 1;
	philo->prev = philo;
	philo->next = philo;
	pthread_mutex_init(&philo->spaghetti_fork, NULL);
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
		lst_add_end(&list_of_philos, lst_new(id, dinner));
	return (list_of_philos);
}
