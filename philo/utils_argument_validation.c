/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_argument_validation.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmigl <hmigl@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 08:06:51 by hmigl             #+#    #+#             */
/*   Updated: 2022/12/26 08:06:56 by hmigl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isnumber(char *number)
{
	int	num_size;
	int	i;

	num_size = ft_strlen(number);
	i = 1;
	if ((number[0] != '-' && number[0] != '+') && !ft_isdigit(number[0]))
		return (0);
	while (i < num_size)
	{
		if (!ft_isdigit(number[i]))
			return (0);
		++i;
	}
	return (1);
}

static int	ft_isspace(int c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

int	ft_atoi(const char *nptr)
{
	int	res;
	int	sig;

	res = 0;
	sig = 1;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
		if (*nptr++ == '-')
			sig *= -1;
	while (ft_isdigit(*nptr))
		res = (*nptr++ - '0') + (res * 10);
	return (res * sig);
}
