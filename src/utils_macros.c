/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_macros.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 21:17:54 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/06/25 09:11:42 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	printf_mutex(t_philo *philo, int action, int i)
{
	pthread_mutex_lock(&philo->data->printfs);
	if (action == EAT)
		printf("\033[0;32m the philo %d is eating...\033[0m\n", philo[i].id);
	else if (action == SLEEP)
		printf("\033[0;34m Sleep... \033[0m %d\n", philo[i].id);
	else if (action == DIED)
		printf("\033[1;31m The philo ID %d is dead! \033[0m\n", philo[i].id);
	pthread_mutex_unlock(&philo->data->printfs);
}

void	action_mutex(t_philo *philo, int action, int i)
{
	pthread_mutex_lock(&philo->data->lock_data);
	if (action == EAT)
	{
		philo->data->eat++;
		printf_mutex(philo, EAT, i);
	}
	else if (action == DIED)
	{
		philo[i].is_dead = true;
		printf_mutex(philo, DIED, i);
	}
}
