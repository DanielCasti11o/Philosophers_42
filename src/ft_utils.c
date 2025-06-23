/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:45:28 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/06/23 17:43:44 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_atoui(const char *nptr)
{
	unsigned int	result;

	result = 0;
	while (*nptr == ' ' || *nptr == '\t' || *nptr == '\n'
		|| *nptr == '\v' || *nptr == '\f' || *nptr == '\r')
	{
		nptr ++;
	}
	while ('0' <= *nptr && *nptr <= '9')
	{
		result = result * 10 + (*nptr - '0');
		nptr ++;
	}
	return (result);
}

void	ft_error(char *msg, int f)
{
	int	i;

	i = 0;
	while (msg[i])
	{
		write(1, &msg[i], 1);
		i++;
	}
	exit(f);
}

int	ft_atol(const char *nptr)
{
	long	result;
	int		chsg;

	chsg = 1;
	result = 0;
	while (*nptr == ' ' || *nptr == '\t' || *nptr == '\n'
		|| *nptr == '\v' || *nptr == '\f' || *nptr == '\r')
		nptr ++;
	if (*nptr == '-')
		ft_error("Value negative not permited\n", 1);
	else if (*nptr == '+')
		nptr ++;
	while ('0' <= *nptr && *nptr <= '9')
	{
		result = result * 10 + (*nptr - '0');
		nptr ++;
	}
	if (result > 2147483647 || result < -2147483647)
		ft_error("Longitud invalida\n", 1);
	return ((int)result * chsg);
}
