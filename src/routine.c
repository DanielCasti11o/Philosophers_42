/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:22:22 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/04/24 18:12:28 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*do_routine(void *arg)
{
	t_philo *philos;
	int		i;

	i = 0;
	philos = (t_philo *)arg;
	while (1)
	{
		printf("\033[0;31m Thinking... \033[0m %d \n", philos->id);
		pthread_mutex_lock(philos->left_fk);
		pthread_mutex_lock(philos->right_fk);
		printf("\033[0;32m the philo %d is eating...\033[0m\n", philos->id);
		philos[i].eat++;
		pthread_mutex_unlock(philos->left_fk);
		pthread_mutex_unlock(philos->right_fk);
		printf("\033[0;34m Sleep... \033[0m %d\n", philos->id);
		usleep(500);
	}
	i++;
	printf("sale bucle %d vez\n", i);
	return (NULL);
}

void    prepare_routine(t_pth *pth)
{
	int i;

	i = 0;
	printf("routiiiine --> %d\n", pth->data->n_philos);
	while (i < pth->data->n_philos)
	{
		pthread_create(&pth->philos[i].thread, NULL, do_routine, (void *)&pth->philos[i]);
		printf("sale %d vez\n", i);
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
