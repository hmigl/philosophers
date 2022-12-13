#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>

typedef struct s_philo_dinner	t_dinner;

struct s_philo_dinner {
	int	nb_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	max_meals;
};

int	has_valid_arguments(int argc, char **argv);

// utils
int	ft_isnumber(char *number);
int	ft_atoi(const char *nptr);

#endif // !PHILO_H
