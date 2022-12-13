#include "philo.h"

static int	is_within_bounds(int argc)
{
	return (argc == 5 || argc == 6);
}

int	has_valid_arguments(int argc, char **argv)
{
	return (is_within_bounds(argc));
}
