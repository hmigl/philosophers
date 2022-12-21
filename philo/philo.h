#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdio.h>

# define OUTPUT_TEMPLATE "%d %d %s\n"
# define FORK "has taken a fork"
# define EAT "is eating"
# define THINK "is thinking"
# define SLEEP "is sleeping"
# define DIE "died"

typedef struct s_philo_dinner	t_dinner;
typedef struct s_philo			t_philo;

struct s_philo {
	int				id;
	t_dinner		*dinner;
	int				meals;
	pthread_mutex_t	spaghetti_fork;
	pthread_t		thread;
	struct s_philo	*prev;
	struct s_philo	*next;
};

struct s_philo_dinner {
	int				nb_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meals;
	int				everybody_alive;
	t_philo			*list_of_philos;
	pthread_mutex_t	everybody_alive_mutex;
	pthread_mutex_t	log_mutex;
};

// validation
int		has_valid_arguments(int argc, char **argv);

// data structures management
t_philo	*new_list(t_dinner *dinner);
void	unset_table(t_dinner *dinner);
void	clear_list(t_dinner *dinner);

// business logic
void	*start_routine(void *arg);
int		dinner_must_end(t_philo *philo);
void	eating_action(t_philo *philo);
void	dinner_log(t_philo *philo, char *action);

// utils
int		ft_isnumber(char *number);
int		ft_atoi(const char *nptr);

#endif // !PHILO_H
