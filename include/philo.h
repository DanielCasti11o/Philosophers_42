/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:01:43 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/04/10 12:41:11 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include "../libft_bonus/libft.h"

typedef struct s_datash
{
	int n_philos; // num de philos
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int eat_required; // comidas requeridas para acabar
	pthread_mutex_t *forks; // array de mutexes para los tenedores
	pthread_mutex_t prints; // para proteger impresiones
	int end_sim;
}   t_datash;

typedef struct s_philo
{
	int id; // identify
	int eat;
	pthread_t thread;
	pthread_mutex_t *right_fk; // tenedores
	pthread_mutex_t *left_fk;

}   t_philo;

typedef struct s_pth
{
	t_datash    data;
	t_philo     *philos;
}t_pth  ;

long ft_atol(const char *nptr);
void    ft_error(char *msg, int f);
void    check_str(char *arg);
void   checkargs(int argc, char **argv);
t_pth   *init_struct(char **argv);
t_datash    init_data(char **argv);
t_philo *init_philos(t_datash data);
void    prepare_routine(t_pth *pth);


void	*ft_philos(void *arg);


#endif
