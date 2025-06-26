/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:22:22 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/06/26 02:26:45 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*monitor_keep(void *arg)
{
	t_philo		*philo;
	t_datash	*data;
	int			i;

	philo = (t_philo *)arg;
	data = philo->data;
	while (1)
	{
		pthread_mutex_lock(&data->stop);
		if (data->dead_flag)
		{
			pthread_mutex_unlock(&data->stop);
			break ;
		}
		pthread_mutex_unlock(&data->stop);
		i = 0;
		while (i < data->n_philos)
		{
			if (check_death(philo, i))
				return (NULL);
			i++;
		}
		usleep(100);
	}
	return (NULL);
}

void	get_times(t_philo *philos)
{
	struct timeval	start;
	long long		milsegs;
	long long		end_time;

	gettimeofday(&start, NULL);
	milsegs = (start.tv_sec * 1000) + (start.tv_usec / 1000);
	philos->data->start_time = milsegs;
	end_time = milsegs + philos->data->time_to_die;
	philos->data->end_sim = end_time;
}

int	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock_data);
	if (philo->data->dead_flag)
	{
		pthread_mutex_unlock(&philo->data->lock_data);
		return (0);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->lock_data);
		pthread_mutex_lock(philo->left_fk);
		pthread_mutex_lock(philo->right_fk);
		if (philo->data->dead_flag)
		{
			pthread_mutex_unlock(&philo->data->lock_data);
			pthread_mutex_unlock(philo->left_fk);
			pthread_mutex_unlock(philo->right_fk);
			return (0);
		}
		printf_mutex(philo, FORKS);
		new_last_meal(philo);
		return (1);
	}
}

void	*do_routine(void *arg)
{
	t_philo		*philo;
	t_datash	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	philo->last_eat = get_time();
	if (case_one_philo(philo))
		return (NULL);
	if ((philo->id % 2) == 0)
		usleep(philo->data->time_to_eat * 1000 / 2);
	while (!philo->data->dead_flag)
	{
		if (!take_forks(philo) || !handle_stop(data, philo))
			break ;
		printf_mutex(philo, THINK);
		new_last_meal(philo);
		printf_mutex(philo, EAT);
		usleep(philo->data->time_to_eat * 1000);
		if (!update_meal(philo) || !handle_stop(data, philo))
			break ;
		printf_mutex(philo, SLEEP);
		usleep(philo->data->time_to_sleep * 1000);
	}
	return (NULL);
}

void	prepare_routine(t_pth *pth)
{
	int	i;

	i = 0;
	get_times(pth->philos);
	while (i < pth->data->n_philos)
	{
		if (pthread_create(&pth->philos[i].thread, NULL,
				do_routine, &pth->philos[i]) != 0)
		{
			ft_error("ERROR: crear el hilo\n", 1);
			return ;
		}
		usleep(100);
		i++;
	}
	pth->n_threads = i;
}
