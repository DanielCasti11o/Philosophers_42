/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:59:52 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/03/31 21:44:24 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

	// ARGUMENTS
	// argv[1] number_of_philosophers
	// argv[2] time_to_die
	// argv[3] time_to_eat
	// argv[4] time_to_sleep
	// argv[5] (OPTIONAL) number_of_times_each_philosopher_must_eat

#include "../include/philo.h"

void    *ft_message(void *arg)
{
	static int i_threads = 0; // pos que iremos iterando para comparar con el hilo muteado
	unsigned int i;
	t_pth *thread;
	thread = (t_pth *)arg;
	thread->skip_thread = 2; // el que saltaremos
	char *msg;
	msg = "Hola\n";
	pthread_mutex_lock(&thread->mutex);
	i = 0;
	printf("HILO %d\n", i_threads);
	while(msg[i] && i_threads != thread->skip_thread)
	{
		write(1, &msg[i], 1);
		i++;
	}
	i_threads++;
	pthread_mutex_unlock(&thread->mutex);
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
	threads = malloc(sizeof(t_pth));
	threads->thread = malloc(num_philos * sizeof(pthread_t));
	pthread_mutex_init(&threads->mutex, NULL);
	i = 0;
	if (argc > 5 || argc < 4)
		return (0);
	while (i < num_philos)
	{
		pthread_create(&threads->thread[i], NULL, ft_message, threads);
		i++;
	}
	i = 0;
	while (i < num_philos)
	{
		pthread_join(threads->thread[i], NULL);
		i++;
	}
	pthread_mutex_destroy(&threads->mutex);
	free(threads->thread);
	free(threads);
}
