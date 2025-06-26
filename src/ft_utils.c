/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:45:28 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/06/25 23:41:52 by daniel-cast      ###   ########.fr       */
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

int	ft_error(char *msg, int f)
{
	int	i;

	i = 0;
	while (msg[i])
	{
		write(1, &msg[i], 1);
		i++;
	}
	return (0);
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

int	ft_sleep(t_philo *philo)
{
	printf_mutex(philo, SLEEP);
	usleep(philo->data->time_to_sleep * 1000);
	return (0);
}

long	get_time(void)
{
	struct timeval	start;
	long long		milsegs;

	gettimeofday(&start, NULL);
	milsegs = (start.tv_sec * 1000) + (start.tv_usec / 1000);
	return (milsegs);
}
