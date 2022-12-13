#include "philo.h"

#define RTFM "usage: ./philo number_of_philosophers time_to_die time_to_eat\
 time_to_sleep [max_meals]\n"

static int	rtfm(void)
{
	write(STDERR_FILENO, RTFM, 88);
	return (1);
}

int	main(int argc, char *argv[])
{
	if (!has_valid_arguments(argc, argv + 1))
		return (rtfm());
	return (0);
}
