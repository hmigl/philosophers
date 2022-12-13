#ifndef PHILO_H
# define PHILO_H

typedef struct s_philo_dinner	t_dinner;

struct s_philo_dinner {
	int	nb_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	max_meals;
};

int	has_valid_arguments(int argc, char **argv);

#endif // !PHILO_H
