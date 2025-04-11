/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:16:23 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/04/10 12:40:31 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

	// ARGUMENTS
	// argv[1] number_of_philosophers
	// argv[2] time_to_die
	// argv[3] time_to_eat
	// argv[4] time_to_sleep
	// argv[5] (OPTIONAL) number_of_times_each_philosopher_must_eat

int main (int argc, char **argv)
{
	t_pth   *pth;
	checkargs(argc, argv);
	pth = init_struct(argv);
	prepare_routine(pth);

	printf("OK\n");
}
