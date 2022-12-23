#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>

# define OUTPUT_TEMPLATE "%ld %d %s\n"
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
	struct timeval	last_meal;
	pthread_mutex_t	spaghetti_fork;
	pthread_t		thread;
	struct s_philo	*prev;
	struct s_philo	*next;
};

struct s_philo_dinner {
	int				nb_of_philosophers;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				max_meals;
	int				everybody_alive;
	struct timeval	elapsed_time_dinner_started;
	t_philo			*list_of_philos;
	pthread_mutex_t	everybody_alive_mutex;
	pthread_mutex_t	log_mutex;
	pthread_t		thread;
};

// validation
int				has_valid_arguments(int argc, char **argv);

// data structures management
t_philo			*new_list(t_dinner *dinner);
void			unset_table(t_dinner *dinner);
void			clear_list(t_dinner *dinner);

// business logic
void			*start_routine(void *arg);
void			*death_routine(void *arg);
int				get_dinner_must_end(t_philo *philo);
void			set_dinner_must_end(t_philo *philo);
void			eating_action(t_philo *philo);
void			sleeping_action(t_philo *philo);

// log
void			dinner_log(t_philo *philo, char *action);
unsigned int	get_time_in_ms_since_event(struct timeval event);

// utils
int				ft_isnumber(char *number);
int				ft_atoi(const char *nptr);

#endif // !PHILO_H
