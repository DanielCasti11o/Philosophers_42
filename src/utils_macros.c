/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_macros.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 21:17:54 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/06/25 21:37:33 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	printf_mutex(t_philo *philo, int action)
{
	pthread_mutex_lock(&philo->data->printfs);
	if (action == EAT)
		printf("\033[0;32m %ld the philo %d is eating...\033[0m\n",
			(get_time() - philo->data->start_time), philo->id);
	else if (action == SLEEP)
		printf("\033[0;34m %ld Sleep... \033[0m %d\n",
			(get_time() - philo->data->start_time), philo->id);
	else if (action == DIED)
		printf("\033[1;31m %ld The philo ID %d is dead! \033[0m\n",
			(get_time() - philo->data->start_time), philo->id);
	else if (action == THINK)
		printf("\033[0;31m %ld Thinking... \033[0m { %d } \n",
			(get_time() - philo->data->start_time), philo->id);
	else if (action == FORK)
		printf("\033[1;33m %ld The philo %d has taken a fork\033[0m\n",
			(get_time() - philo->data->start_time), philo->id);
	else if (action == FORKS)
	{
		printf("\033[1;33m%ld The philo %d has taken a fork\033[0m\n",
			(get_time() - philo->data->start_time), philo->id);
		printf("\033[1;33m%ld The philo %d has taken a fork\033[0m\n",
			(get_time() - philo->data->start_time), philo->id);
	}
	pthread_mutex_unlock(&philo->data->printfs);
}

void	action_mutex(t_philo *philo, int action)
{
	if (action == DIED)
	{
		printf_mutex(philo, DIED);
		return ;
	}
	pthread_mutex_lock(&philo->data->lock_data);
	if (action == DIED_FLAG)
	{
		philo->is_dead = true;
		philo->data->dead_flag = true;
		pthread_mutex_unlock(&philo->data->lock_data);
		return ;
	}
	if (action == EAT)
		philo->eat++;
	pthread_mutex_unlock(&philo->data->lock_data);
}

int	exit_to_program(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock_data);
	if (philo->data->dead_flag == true)
	{
		pthread_mutex_unlock(&philo->data->lock_data);
		return (0);
	}
	if ((get_time() - philo->last_eat) >= philo->data->time_to_die
		|| (get_time() - philo->data->start_time) >= philo->data->time_to_die)
	{
		philo->is_dead = true;
		philo->data->dead_flag = true;
		pthread_mutex_unlock(&philo->data->lock_data);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->lock_data);
		return (1);
	}
}

int	case_one_philo(t_philo *philo)
{
	if (philo->data->n_philos == 1)
	{
		pthread_mutex_lock(philo->left_fk);
		printf_mutex(philo, FORK);
		usleep(philo->data->time_to_die * 1000);
		pthread_mutex_unlock(philo->left_fk);
		return (1);
	}
	else
		return (0);
}

void	new_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock_data);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->data->lock_data);
}
