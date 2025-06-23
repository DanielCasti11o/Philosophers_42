/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:22:22 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/06/23 20:05:35 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	keeper_monitor(t_pth *pth)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&pth->data->death);
	while (pth->philos[i].is_dead != true)
	{
		if (pth->philos[i].is_dead == true)
		{
			printf("\033[1;31m The philo ID %d is dead! \033[0m\n");
			pthread_mutex_unlock(&pth->data->death);
			pthread_mutex_destroy(&pth->data->death);
			return ;
		}
		i++;
	}
	pthread_mutex_unlock(&pth->data->death);
}

void	get_times(t_philo *philos)
{
	struct timeval	start;
	unsigned int	milsegs;
	long			end_time;

	gettimeofday(&start, NULL);
	milsegs = (start.tv_sec * 1000) + (start.tv_usec / 1000);
	end_time = (philos->data->time_to_die * 1000) + milsegs;
	philos->data->end_sim = end_time;
	philos->data->time_to_eat *= 1000; // pasarlo a milisegs
	philos->data->time_to_sleep *= 1000;
	philos->data->start_time = milsegs;
	printf("tiempo --> %ld\n", milsegs);
	printf("ÑÑÑÑÑÑÑ  tiempo time to eat --> %ld  ÑÑÑÑÑÑÑ \n", philos->data->time_to_eat);
	printf("ZZZZZZZ  tiempo time to sleep --> %ld  ZZZZZ \n", philos->data->time_to_sleep);
	printf("END  tiempo fin de simulacion --> %ld  END   \n", end_time);
}

void	ft_sleep(t_philo *philo, int i)
{
	philo[i].data->start_time += philo[i].data->time_to_sleep;
	printf("\033[0;34m Sleep... \033[0m %d\n", philo[i].id);
	// if (philo.data->start_time >= philo.data->end_sim)
	// {
	// 	philo.is_dead = true;
	// 	return ;
	// 			// printf("sale\n");
	// 	// exit(1);
	// }
}

void	*do_routine(void *arg)
{
	t_philo		*philos;
	t_datash	*data;
	int			i;

	i = 0;
	philos = (t_philo *)arg;
	get_times(philos);
	while (1)
	{
		printf("\033[0;31m Thinking... \033[0m { %d } \n", philos->id);
		if (data->eat <= data->eat_required)
		{
			pthread_mutex_lock(philos[i].left_fk);
			pthread_mutex_lock(philos[i].right_fk);
			data->eat++;
			data->start_time += data->time_to_eat;
			printf("\033[0;32m the philo %d is eating...\033[0m\n", philos->id);
			pthread_mutex_unlock(philos[i].left_fk);
			pthread_mutex_unlock(philos[i].right_fk);
		}
		else
			exit(1);
		if (data->start_time >= data->end_sim)
			philos[i].is_dead = true;
		ft_sleep(philos, i);
		// printf("\033[0;34m Sleep... \033[0m %d\n", philos->id);
		i++;
	}
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
		pthread_join(pth->philos[i].thread, NULL); // Espera que uno de los hilos acabe la ejecucion
		i++;
	}
	i = 0;
	while (i < pth->data->n_philos)
	{
		pthread_mutex_destroy(&pth->data->forks[i]);
		i++;
	}
}
