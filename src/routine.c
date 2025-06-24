/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:22:22 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/06/24 22:07:19 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*keeper_monitor(void *arg)
{
	int		i;
	t_pth	*pth;

	pth = (t_pth *)arg;
	i = 0;
	printf("monitor\n");
	if (pth->philos[i].is_dead == true)
	{
		printf("\033[1;31m The philo ID %d is dead! \033[0m\n", pth->philos[i].id);
		pthread_mutex_unlock(&pth->data->death);
		pthread_mutex_destroy(&pth->data->death);
		return (NULL);
	}
	while (pth->philos[i].is_dead != true)
	{
		pthread_mutex_lock(&pth->data->death);
		if (pth->philos[i].is_dead == true)
		{
			printf("\033[1;31m The philo ID %d is dead! \033[0m\n", pth->philos[i].id);
			pthread_mutex_unlock(&pth->data->death);
			pthread_mutex_destroy(&pth->data->death);
			return (NULL);
		}
		pthread_mutex_unlock(&pth->data->death);
		i++;
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
	// printf("tiempo --> %lld\n", milsegs);
	// printf("ÑÑÑÑÑÑÑ time to eat --> %d  ÑÑ \n", philos->data->time_to_eat);
	// printf("ZZZZZZZ time to sleep --> %d  ZZ \n", philos->data->time_to_sleep);
	// printf("END  tiempo fin de simulacion --> %lld  END   \n", end_time);
}

void	take_forks(t_philo *philo, int i)
{
	if ((philo[i].id % 2) == 0)
	{
		pthread_mutex_lock(philo[i].left_fk);
		pthread_mutex_lock(philo[i].right_fk);
	}
	else
	{
		pthread_mutex_lock(philo[i].right_fk);
		pthread_mutex_lock(philo[i].left_fk);
	}
	philo->data->last_eat = get_time();
	philo->data->eat++;
	printf("\033[0;32m the philo %d is eating...\033[0m\n", philo[i].id);
	ft_usleep(philo->data->last_eat, philo->data->time_to_die, philo, i);
	pthread_mutex_unlock(philo[i].left_fk);
	pthread_mutex_unlock(philo[i].right_fk);
}

void	*do_routine(void *arg)
{
	t_philo		*philos;
	t_datash	*data;
	int			i;

	i = 0;
	philos = (t_philo *)arg;
	data = philos->data;
	get_times(philos);
	while (1)
	{
		printf("\033[0;31m Thinking... \033[0m { %d } \n", philos[i].id);
		if (data->eat < data->eat_required)
		{
			// printf("ENTRA POR AQUI!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
			take_forks(philos, i);
		}
		if ((get_time() - data->last_eat) >= data->time_to_die)
		{
			philos[i].is_dead = true;
			printf("\033[1;31m The philo ID %d is dead! \033[0m\n", philos[i].id);
			break ;
		}
		ft_sleep(philos, i);
		// printf("\033[0;34m Sleep... \033[0m %d\n", philos->id);
		i = (i + 1) % data->n_philos;
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
		if (pthread_create(&pth->philos[i].thread, NULL, do_routine, (void *)&pth->philos[i]) != 0)
			ft_error("ERROR: crear el hilo\n", 1);
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
