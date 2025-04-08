/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:59:52 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/04/07 21:32:40 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

	// ARGUMENTS
	// argv[1] number_of_philosophers
	// argv[2] time_to_die
	// argv[3] time_to_eat
	// argv[4] time_to_sleep
	// argv[5] (OPTIONAL) number_of_times_each_philosopher_must_eat

#include "../include/philo.h"

// void    *ft_message(void *arg)
// {
// 	static int i_threads = 0; // pos que iremos iterando para comparar con el hilo muteado
// 	unsigned int i;
// 	t_pth *thread;
// 	thread = (t_pth *)arg;
// 	thread->skip_thread = 2; // el que saltaremos
// 	char *msg;
// 	msg = "Hola\n";
// 	pthread_mutex_lock(&thread->mutex);
// 	i = 0;
// 	printf("HILO %d\n", i_threads);
// 	while(msg[i] && i_threads != thread->skip_thread)
// 	{
// 		write(1, &msg[i], 1);
// 		i++;
// 	}
// 	i_threads++;
// 	pthread_mutex_unlock(&thread->mutex);
// 	return (NULL);
// }

void	*ft_philos(void *arg)
{
	// static int      i_threads;
	unsigned int    i;
	t_pth           *thread;
	thread = (t_pth *)arg;

	i = 1;

	while (1)
	{
		printf("philo piensa N-%d\n", i);
		usleep(500000);
		pthread_mutex_lock(&thread->mutex);
		printf("philo come N-%d\n", i);
		usleep(500000);
		pthread_mutex_unlock(&thread->mutex);
		printf("philo duerme N-%d\n", i);
		usleep(500000);
		if (i == 4)
		{
			printf("\n");
			i = 1;
		}
		i++;
	}

	return (NULL);
}

// void    init(t_pth *threads)
// {
//
// }

int main(int argc, char **argv)
{
	int i;
	t_pth *threads;
	int num_philos;

	num_philos = atoi(argv[1]);
	printf("num philos --> %d\n", num_philos);
	threads = malloc(sizeof(t_pth));
	threads->thread = malloc(num_philos * sizeof(pthread_t));
	pthread_mutex_init(&threads->mutex, NULL);
	i = 0;
	if (argc > 6)
		return (0);
	printf("num philos --> %d\n", num_philos);
	while (i < num_philos)
	{
		pthread_create(&threads->thread[i], NULL, ft_philos, threads);
		i++;
	}
	i = 0;
	while (i < num_philos)
	{
		pthread_join(threads->thread[i], NULL);
		i++;
	}
	pthread_mutex_destroy(threads->mutex);
	free(threads->thread);
	free(threads);
}
