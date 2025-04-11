/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:22:22 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/04/10 16:05:29 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void    do_routine(t_pth *pth)
{
	
}

void    prepare_routine(t_pth *pth)
{
	int i;

	i = 0;
	while (i < pth->data.n_philos)
	{
		pthread_create(&pth->philos[i].thread, NULL, do_routine, pth);
		i++;
	}
	i = 0;
	while (i < pth->data.n_philos)
	{
		pthread_mutex_destroy(&pth->philos[i].thread);
		i++;
	}

}
