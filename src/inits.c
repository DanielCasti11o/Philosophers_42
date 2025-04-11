/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:45:21 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/04/10 12:47:05 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

pthread_mutex_t *init_forks(int n_philos)
{
	int i;
	pthread_mutex_t *forks;

	forks = malloc(n_philos * sizeof(pthread_mutex_t));
	if (!forks)
		return (NULL);
	i = 0;
	while (i < n_philos)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			while (i >= 0)
			{
				pthread_mutex_destroy(&forks[i]);
				i--;
			}
			free(forks);
			return (NULL);
		}
		i++;
	}
	return (forks);
}

t_datash    init_data(char **argv)
{
	t_datash data;

	data.n_philos = ft_atol(argv[1]);
	if (data.n_philos > 200)
		ft_error("ERROR: limit exceeded to N_PHILOS\n", 1);
	data.time_to_die = ft_atol(argv[2]);
	data.time_to_eat = ft_atol(argv[3]);
	data.time_to_sleep = ft_atol(argv[4]);
	if (argv[5])
		data.eat_required = ft_atol(argv[5]);
	else
		data.eat_required = 0;
	data.end_sim = ft_atol(argv[2]); // aún no esta comprobado bien esta variable
	data.forks = init_forks(data.n_philos);
}

t_philo *init_philos(t_datash data)
{
	t_philo *philo;
	int i;

	i = 0;
	philo = malloc(data.n_philos * sizeof(t_philo));
	while (i < data.n_philos)
	{
		philo[i].id = i;
		philo[i].left_fk = &data.forks[i];
		philo[i].right_fk = &(data.forks[(i + 1) % data.n_philos]);
		philo[i].eat = 0;
		i++;
	}
	return (philo);
}

t_pth   *init_struct(char **argv)
{
	t_pth *pth;

	pth = malloc(sizeof(t_pth));
	if (!pth)
		ft_error("ERROR: allocated memory \n", 1);
	pth->data = init_data(argv);
	pth->philos = init_philos(pth->data);
	do_routine(pth);
}
