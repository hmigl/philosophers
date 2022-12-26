/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_validation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmigl <hmigl@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 08:06:50 by hmigl             #+#    #+#             */
/*   Updated: 2022/12/26 08:06:56 by hmigl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_positive(char **argv)
{
	int	i;

	i = -1;
	while (argv[++i] != NULL)
	{
		if (!ft_isnumber(argv[i]))
			return (0);
		if (ft_atoi(argv[i]) <= 0)
			return (0);
	}
	return (1);
}

static int	is_within_bounds(int argc)
{
	return (argc == 5 || argc == 6);
}

int	has_valid_arguments(int argc, char **argv)
{
	return (is_within_bounds(argc) && is_positive(argv));
}
