/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:16:23 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/06/26 02:22:18 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

	// ARGUMENTS
	// argv[1] number_of_philosophers
	// argv[2] time_to_die
	// argv[3] time_to_eat
	// argv[4] time_to_sleep
	// argv[5] (OPTIONAL) number_of_times_each_philosopher_must_eat

void	joins_threads(t_pth *pth)
{
	int	i;

	i = 0;
	if (!pth->data)
		return ;
	while (i < pth->n_threads)
	{
		if (pth->philos[i].thread)
		{
			pthread_join(pth->philos[i].thread, NULL);
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_pth		*pth;
	pthread_t	keeper;

	if (!checkargs(argc, argv))
		return (0);
	pth = init_struct(argv);
	if (!pth)
		return (0);
	prepare_routine(pth);
	if (pthread_create(&keeper, NULL, monitor_keep, (void *)pth->philos) != 0)
		ft_error("ERROR: create thread!", 1);
	pthread_join(keeper, NULL);
	joins_threads(pth);
	free_pth(pth);
}
