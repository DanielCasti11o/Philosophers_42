/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 19:18:32 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/06/25 22:21:50 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	time_over(long current_time, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock_data);
	if ((current_time - philo->last_eat) >= philo->data->time_to_die)
	{
		philo->data->dead_flag = 1;
		pthread_mutex_unlock(&philo->data->lock_data);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->lock_data);
	return (1);
}

int	handle_mutex_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock_data);
	if (philo->data->dead_flag)
	{
		pthread_mutex_unlock(&philo->data->lock_data);
		pthread_mutex_unlock(philo->left_fk);
		pthread_mutex_unlock(philo->right_fk);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->lock_data);
	return (1);
}
