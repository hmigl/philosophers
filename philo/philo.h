#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>

typedef struct s_philo_dinner	t_dinner;
typedef struct s_philo			t_philo;

struct s_philo {
	int				id;
	struct s_philo	*prev;
	struct s_philo	*next;
	pthread_mutex_t	spaghetti_fork;

};

struct s_philo_dinner {
	int		nb_of_philosophers;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		max_meals;
	t_philo	*list_of_philos;
};

int		has_valid_arguments(int argc, char **argv);
void	set_table(t_dinner *dinner);
t_philo	*new_list(t_dinner *dinner);

// utils
int		ft_isnumber(char *number);
int		ft_atoi(const char *nptr);

#endif // !PHILO_H
