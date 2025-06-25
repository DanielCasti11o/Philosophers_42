/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:22:22 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/06/25 17:56:47 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*keeper_monitor(void *arg)
{
	t_pth	*pth;
	int		i;

	pth = (t_pth *)arg;
	while (1)
	{
		i = 0;
		while (i < pth->data->n_philos)
		{
			pthread_mutex_lock(&pth->data->lock_data);
			if (pth->philos[i].is_dead == true || pth->data->dead_flag)
			{
				action_mutex(&pth->philos[i], DIED);
				pthread_mutex_unlock(&pth->data->lock_data);
				return (NULL);
			}
			pthread_mutex_unlock(&pth->data->lock_data);
			i++;
		}
		usleep(100);
	}
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

void	take_forks(t_philo *philo)
{
	if (case_one_philo(philo) == 1)
		return ;
	pthread_mutex_lock(&philo->data->lock_data);
	if (philo->data->dead_flag)
	{
		pthread_mutex_unlock(&philo->data->lock_data);
		return ;
	}
	pthread_mutex_unlock(&philo->data->lock_data);
	if ((philo->id % 2) == 0)
	{
		pthread_mutex_lock(philo->left_fk);
		pthread_mutex_lock(philo->right_fk);
	}
	else
	{
		pthread_mutex_lock(philo->right_fk);
		pthread_mutex_lock(philo->left_fk);
	}
	printf_mutex(philo, FORKS);
	pthread_mutex_lock(&philo->data->lock_data);
	if (philo->data->dead_flag)
	{
		pthread_mutex_unlock(&philo->data->lock_data);
		pthread_mutex_unlock(philo->left_fk);
		pthread_mutex_unlock(philo->right_fk);
		return ;
	}
	ft_usleep(philo->last_eat, philo->data->time_to_eat, philo);
	pthread_mutex_unlock(&philo->data->lock_data);
	action_mutex(philo, EAT);
	pthread_mutex_unlock(philo->left_fk);
	pthread_mutex_unlock(philo->right_fk);
}

void	*do_routine(void *arg)
{
	t_philo		*philo;
	t_datash	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (1)
	{
		pthread_mutex_lock(&data->lock_data);
		if (data->dead_flag == true)
		{
			pthread_mutex_unlock(&data->lock_data);
			return (NULL);
		}
		pthread_mutex_unlock(&data->lock_data);
		printf_mutex(philo, THINK);
		if (data->dead_flag == false
			&& (data->eat < data->eat_required || data->eat_required == -1))
			take_forks(philo);
		if (!exit_to_program(philo))
			return (NULL);
		ft_sleep(philo);
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
				do_routine, (void *)&pth->philos[i]) != 0)
			ft_error("ERROR: crear el hilo\n", 1);
		i++;
	}
	i = 0;
	while (i < pth->data->n_philos)
	{
		pthread_join(pth->philos[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < pth->data->n_philos)
	{
		pthread_mutex_destroy(&pth->data->forks[i]);
		i++;
	}
}
