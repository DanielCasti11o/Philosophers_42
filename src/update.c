/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 23:35:01 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/06/26 02:37:58 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	update_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock_data);
	if (philo->data->dead_flag)
	{
		pthread_mutex_unlock(philo->left_fk);
		pthread_mutex_unlock(philo->right_fk);
		pthread_mutex_unlock(&philo->data->lock_data);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->lock_data);
	pthread_mutex_lock(&philo->data->lock_data);
	philo->eat++;
	if (philo->data->eat_required > 0
		&& philo->eat == philo->data->eat_required)
	{
		pthread_mutex_lock(&philo->data->printfs);
		philo->data->eat_fin++;
		if (philo->data->eat_fin == philo->data->n_philos)
			philo->data->dead_flag = true;
		pthread_mutex_unlock(&philo->data->printfs);
	}
	pthread_mutex_unlock(&philo->data->lock_data);
	pthread_mutex_unlock(philo->left_fk);
	pthread_mutex_unlock(philo->right_fk);
	return (1);
}

int	check_death(t_philo *philo, int i)
{
	long	elapsed;

	pthread_mutex_lock(&philo->data->lock_data);
	elapsed = get_time() - philo[i].last_eat;
	pthread_mutex_unlock(&philo->data->lock_data);
	if (elapsed > philo->data->time_to_die)
	{
		printf_mutex(&philo[i], DIED);
		pthread_mutex_lock(&philo->data->stop);
		philo->data->dead_flag = true;
		pthread_mutex_unlock(&philo->data->stop);
		return (1);
	}
	return (0);
}

int	handle_stop(t_datash *data, t_philo *philo)
{
	pthread_mutex_lock(&data->stop);
	if (data->dead_flag)
	{
		pthread_mutex_unlock(&data->stop);
		return (0);
	}
	pthread_mutex_unlock(&data->stop);
	return (1);
}

void	destroys(t_datash *data)
{
	pthread_mutex_destroy(&data->printfs);
	pthread_mutex_destroy(&data->lock_data);
}

void	util_init_data(t_datash *data, char **argv)
{
	data->time_to_die = ft_atoui(argv[2]);
	data->time_to_eat = ft_atoui(argv[3]);
	data->time_to_sleep = ft_atoui(argv[4]);
	if (argv[5])
		data->eat_required = ft_atoui(argv[5]);
	else
		data->eat_required = -1;
	data->end_sim = ft_atoui(argv[2]);
	data->dead_flag = false;
	data->start_time = 0;
	data->eat_fin = 0;
}
