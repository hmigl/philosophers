/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmigl <hmigl@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 08:06:50 by hmigl             #+#    #+#             */
/*   Updated: 2022/12/26 08:06:56 by hmigl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define RTFM "usage: ./philo number_of_philosophers time_to_die time_to_eat\
 time_to_sleep [max_meals]\n"

static int	rtfm(void)
{
	write(STDERR_FILENO, RTFM, 88);
	return (1);
}

static void	store_dinner_info(t_dinner *dinner, char **argv)
{
	*dinner = (t_dinner){
		.nb_of_philosophers = ft_atoi(argv[0]),
		.time_to_die = ft_atoi(argv[1]),
		.time_to_eat = ft_atoi(argv[2]),
		.time_to_sleep = ft_atoi(argv[3])
	};
	dinner->max_meals = -2147483648;
	if (argv[4])
		dinner->max_meals = ft_atoi(argv[4]);
	dinner->everybody_alive = 1;
}

static void	set_table(t_dinner *dinner)
{
	gettimeofday(&(dinner->elapsed_time_dinner_started), NULL);
	dinner->list_of_philos = new_list(dinner);
	pthread_mutex_init(&(dinner->everybody_alive_mutex), NULL);
	pthread_mutex_init(&(dinner->log_mutex), NULL);
	pthread_mutex_init(&(dinner->satisfaction_mutex), NULL);
}

static void	dine(t_dinner *dinner)
{
	int		i;
	t_philo	*philo;

	i = -1;
	philo = dinner->list_of_philos;
	while (++i < dinner->nb_of_philosophers)
	{
		pthread_create(&(philo->thread), NULL, &start_routine, (void *)philo);
		philo = philo->next;
	}
	pthread_create(&(dinner->starvation_thread), NULL,
		&death_routine, (void *)philo);
}

int	main(int argc, char *argv[])
{
	t_dinner	dinner;

	if (!has_valid_arguments(argc, argv + 1))
		return (rtfm());
	store_dinner_info(&dinner, argv + 1);
	set_table(&dinner);
	dine(&dinner);
	unset_table(&dinner);
	return (0);
}
