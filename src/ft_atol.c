/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:45:28 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/04/09 14:52:09 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void    ft_error(char *msg, int f)
{
	int i;

	i = 0;
	while (msg[i])
	{
		write(1, &msg[i], 1);
		i++;
	}
	exit(f);
}

long ft_atol(const char *nptr)
{
	int	result;
	int	chsg;

	chsg = 1;
	result = 0;
	while (*nptr == ' ' || *nptr == '\t' || *nptr == '\n'
		|| *nptr == '\v' || *nptr == '\f' || *nptr == '\r')
		nptr ++;
	if (*nptr == '-')
	{
		chsg = -1;
		nptr ++;
	}
	else if (*nptr == '+')
		nptr ++;
	while ('0' <= *nptr && *nptr <= '9')
	{
		result = result * 10 + (*nptr - '0');
		nptr ++;
	}
	if (result > 2147483647 || result < -2147483647)
		ft_error("Longitud invalida\n", 1);
	return (result * chsg);
}
