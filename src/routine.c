/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:22:22 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/06/23 17:15:30 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	get_times(t_philo *philos)
{
	struct timeval	start;
	unsigned int	milsegs;
	long			end_time;

	gettimeofday(&start, NULL);
	milsegs = (start.tv_sec * 1000) + (start.tv_usec / 1000);
	end_time = (philos->data->time_to_die * 1000) + milsegs;
	philos->data->end_sim = end_time;
	philos->data->time_to_eat += milsegs * 1000; // pasarlo a milisegs
	philos->data->time_to_sleep += milsegs * 1000;
	philos->data->start_time = milsegs;
	printf("tiempo --> %ld\n", milsegs);
	printf("ÑÑÑÑÑÑÑ  tiempo time to eat --> %ld  ÑÑÑÑÑÑÑ \n", philos->data->time_to_eat);
	printf("ZZZZZZZ  tiempo time to sleep --> %ld  ZZZZZ \n", philos->data->time_to_sleep);
	printf("END  tiempo fin de simulacion --> %ld  END   \n", end_time);
}

void	ft_sleep(t_philo *philo)
{
	philo->data->start_time += philo->data->time_to_sleep;
	if (philo->data->start_time >= philo->data->end_sim)
	{
		printf("sale\n");
		exit(1);
	}
}

void	*do_routine(void *arg)
{
	t_philo		*philos;
	t_datash	*data;
	int			i;

	i = 0;
	philos = (t_philo *)arg;
	while (1)
	{
		get_times(philos);
		printf("\033[0;31m Thinking... \033[0m %d \n", philos->id);
		pthread_mutex_lock(philos->left_fk);
		pthread_mutex_lock(philos->right_fk);
		printf("\033[0;32m the philo %d is eating...\033[0m\n", philos->id);
		philos[i].eat++;
		if (philos[i].eat >= data->eat_required)
			break ;
		pthread_mutex_unlock(philos->left_fk);
		pthread_mutex_unlock(philos->right_fk);
		ft_sleep(philos);
		printf("\033[0;34m Sleep... \033[0m %d\n", philos->id);
		usleep(500);
	}
	i++;
	// printf("sale bucle %d vez\n", i);
	return (NULL);
}

void	prepare_routine(t_pth *pth)
{
	int	i;

	i = 0;
	// printf("routiiiine --> %d\n", pth->data->n_philos);
	while (i < pth->data->n_philos)
	{
		pthread_create(&pth->philos[i].thread, NULL, do_routine, (void *)&pth->philos[i]);
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
