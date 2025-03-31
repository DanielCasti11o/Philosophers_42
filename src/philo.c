/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:59:52 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/03/26 18:21:59 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

	// ARGUMENTS
	// argv[1] number_of_philosophers
	// argv[2] time_to_die
	// argv[3] time_to_eat
	// argv[4] time_to_sleep
	// argv[5] (OPTIONAL) number_of_times_each_philosopher_must_eat

#include "../include/philo.h"

void    *ft_message(void *msg)
{
	unsigned int i;
	char *str;
	str = (char *)msg;

	i = 0;
	while(str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (str);
}

// void    init(t_pth *threads)
// {
//
// }

int main(int argc, char **argv)
{
	int i;
	t_pth *threads;

	i = 0;
	if (argc > 5 || argc < 4)
		return (0);
	while (i < atoi(argv[1]))
	{
		pthread_create(threads->thread[i], NULL, ft_message, "hola");
		pthread_join(threads->thread[i], NULL);
		i++;
	}

}
