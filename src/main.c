/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:16:23 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/06/25 16:01:05 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

	// ARGUMENTS
	// argv[1] number_of_philosophers
	// argv[2] time_to_die
	// argv[3] time_to_eat
	// argv[4] time_to_sleep
	// argv[5] (OPTIONAL) number_of_times_each_philosopher_must_eat

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
	pthread_create(&keeper, NULL, keeper_monitor, (void *)pth);
	pthread_join(keeper, NULL);
	free_pth(pth);
}
