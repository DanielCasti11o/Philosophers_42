/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:01:43 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/04/07 21:51:44 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_philo
{
	int id; // identify
	int eat;
	pthread_t thread;
	pthread_mutex_t *right_fk; // tenedores
	pthread_mutex_t *left_fk;
	struct s_data *data; // REF a datos compartidos

}   t_philo;

typedef struct s_data
{


}   t_data;



typedef struct s_pth
{
	pthread_t *thread;
	int skip_thread; // indice del hilo que se saltará gracias al mutex
}t_pth  ;

typedef struct s_philo
{

} t_philo;

void	*ft_philos(void *arg);

#endif
