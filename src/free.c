/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 01:02:17 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/06/26 02:42:37 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	free_forks(pthread_mutex_t *forks, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(forks);
}

void	free_data(t_datash *data)
{
	int	i;

	i = 0;
	if (data)
	{
		while (i < data->n_philos)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		pthread_mutex_destroy(&data->printfs);
		pthread_mutex_destroy(&data->lock_data);
		pthread_mutex_destroy(&data->stop);
		if (data->forks)
			free_forks(data->forks, data->n_philos);
		free(data);
	}
}

void	free_pth(t_pth *pth)
{
	if (pth)
	{
		if (pth->data)
			free_data(pth->data);
		if (pth->philos)
			free(pth->philos);
		free(pth);
	}
}
