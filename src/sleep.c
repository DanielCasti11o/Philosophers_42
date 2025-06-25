/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 19:18:32 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/06/25 21:24:58 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	time_over(long actual, t_philo *philo)
{
	if ((actual - philo->last_eat) >= philo->data->time_to_die)
	{
		action_mutex(philo, DIED_FLAG);
		return (0);
	}
	return (1);
}

void	ft_usleep(long start, long end, t_philo *philo)
{
	long	actual;

	while ((get_time() - start) < end)
	{
		actual = get_time();
		if (!time_over(actual, philo))
			break ;
		usleep(50);
	}
}

int	handle_mutex_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock_data);
	if (philo->data->dead_flag)
	{
		pthread_mutex_unlock(&philo->data->lock_data);
		pthread_mutex_unlock(philo->left_fk);
		pthread_mutex_unlock(philo->right_fk);
	}
	pthread_mutex_unlock(&philo->data->lock_data);
}
