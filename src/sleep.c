/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 19:18:32 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/06/24 22:04:40 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	time_over(long actual, t_philo *philo, int i)
{
	if (actual >= philo->data->time_to_die)
	{
		philo[i].is_dead = true;
		return (0);
	}
	return (1);
}

void	ft_usleep(long long start_eat, long long end_eat, t_philo *philo, int i)
{
	long	actual;

	while ((get_time() - start_eat) >= end_eat)
	{
		actual = get_time();
		if (!time_over((actual - start_eat), philo, i))
			break ;
		usleep(100);
	}
}
