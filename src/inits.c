/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacastil <dacastil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:45:21 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/06/26 03:22:34 by dacastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

pthread_mutex_t	*init_forks(int n_philos)
{
	int				i;
	pthread_mutex_t	*forks;

	if (n_philos <= 0)
		return (NULL);
	forks = malloc(n_philos * sizeof(pthread_mutex_t));
	if (!forks)
		return (NULL);
	i = 0;
	while (i < n_philos)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&forks[i]);
			free(forks);
			return (NULL);
		}
		i++;
	}
	return (forks);
}

int	ft_controls(t_datash *data)
{
	if (data->time_to_die < data->time_to_eat
		|| data->time_to_die < data->time_to_sleep)
		return (printf("ERROR: insufficient time! \n"), 0);
	else
		return (1);
}

t_datash	*init_data(char **argv)
{
	t_datash	*data;

	data = malloc(sizeof(t_datash));
	if (!data)
		return (NULL);
	memset(data, 0, sizeof(*data));
	data->n_philos = ft_atoui(argv[1]);
	if (data->n_philos > 200)
		ft_error("ERROR: limit exceeded to N_PHILOS\n", 1);
	util_init_data(data, argv);
	if (pthread_mutex_init(&data->printfs, NULL)
		|| pthread_mutex_init(&data->lock_data, NULL))
		return (pthread_mutex_destroy(&data->stop), NULL);
	if (pthread_mutex_init(&data->lock_data, NULL))
		return (destroys(data), NULL);
	data->forks = init_forks(data->n_philos);
	if (!data->forks)
		return (free(data), NULL);
	return (data);
}

t_philo	*init_philos(t_datash *data)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = malloc(data->n_philos * sizeof(t_philo));
	if (!philo)
		return (NULL);
	memset(philo, 0, sizeof(t_philo));
	while (i < data->n_philos)
	{
		philo[i].id = i;
		philo[i].left_fk = &data->forks[i];
		philo[i].right_fk = &(data->forks[(i + 1) % data->n_philos]);
		philo[i].is_dead = false;
		philo[i].last_eat = get_time();
		philo[i].eat = 0;
		philo[i].data = data;
		i++;
	}
	return (philo);
}

t_pth	*init_struct(char **argv)
{
	t_pth	*pth;

	pth = malloc(sizeof(t_pth));
	if (!pth)
		ft_error("ERROR: allocated memory \n", 1);
	pth->data = init_data(argv);
	if (!pth->data)
		return (ft_error("ERROR: allocated memory \n", 1), free(pth), NULL);
	pth->philos = init_philos(pth->data);
	if (!pth->philos)
		return (free_data(pth->data), free(pth), NULL);
	pth->n_threads = 0;
	return (pth);
}
