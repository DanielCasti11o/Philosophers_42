/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:45:21 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/04/24 12:03:06 by daniel-cast      ###   ########.fr       */
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
			printf("dede\n");
			while (i >= 0)
			{
				printf("uy\n");
				pthread_mutex_destroy(&forks[i]);
				i--;
			}
			free(forks);
			return (NULL);
		}
		printf("nnn--> %d\n", i);
			i++;
	}
	printf("sale good\n");
	return (forks);
}

t_datash    *init_data(char **argv)
{
	t_datash	*data;

	data = malloc(sizeof(t_datash));
	data->n_philos = ft_atol(argv[1]);
	printf("n_philos --> %d\n", data->n_philos);
	if (data->n_philos > 200)
		ft_error("ERROR: limit exceeded to N_PHILOS\n", 1);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	if (argv[5])
		data->eat_required = ft_atol(argv[5]);
	else
		data->eat_required = 0;
	data->end_sim = ft_atol(argv[2]); // aún no esta comprobado bien esta variable
	printf("n_philosss --> %d\n", data->n_philos);
	data->forks = init_forks(data->n_philos);
	if (!data->forks)
		return (free(data), NULL);
	printf("n_philos aiba--> %d\n", data->n_philos);
	return (data);
}

t_philo *init_philos(t_datash *data)
{
	t_philo *philo;
	int i;

	i = 0;
	printf("sabes --> %d\n", data->n_philos);

	philo = malloc(data->n_philos * sizeof(t_philo));
	while (i < data->n_philos)
	{
		printf("entra al bucle --> i---> %d philos-->%d \n", i, data->n_philos);
		philo[i].id = i;
		philo[i].left_fk = &data->forks[i];
		printf("aqui esta\n");
		philo[i].eat= 0;
		philo[i].right_fk = &(data->forks[(i + 1) % data->n_philos]);
		printf("el problema\n");
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
		return (printf("sale pai\n"), free(pth), NULL);
	printf("saliross\n");
	printf("n_philos aibaros --> %d\n", pth->data->n_philos);
	pth->philos = init_philos(pth->data);
	return (pth);
	// do_routine(pth);
}
