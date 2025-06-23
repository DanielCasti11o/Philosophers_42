/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:01:43 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/06/23 19:40:25 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include "../libft_bonus/libft.h"

typedef struct s_datash
{
	unsigned int	n_philos; // num de philos
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	eat_required; // comidas requeridas para acabar
	pthread_mutex_t	*forks; // array de mutexes para los tenedores
	pthread_mutex_t	death;
	unsigned int	end_sim;
	int				eat;
	unsigned int	start_time;

}	t_datash;

typedef struct s_philo
{
	int				id; // identify
	pthread_t		thread;
	pthread_mutex_t	*right_fk; // tenedores
	pthread_mutex_t	*left_fk;
	t_datash		*data;
	bool			is_dead;

}	t_philo;

typedef struct s_pth
{
	t_datash	*data;
	t_philo		*philos;
}	t_pth;

int			ft_atol(const char *nptr);
int			ft_atoui(const char *nptr);
void		ft_error(char *msg, int f);
void		check_str(char *arg, int argc);
void		checkargs(int argc, char **argv);
t_pth		*init_struct(char **argv);
t_datash	*init_data(char **argv);
t_philo		*init_philos(t_datash *data);
void		prepare_routine(t_pth *pth);
void		*do_routine(void *arg);
void		keeper_monitor(t_pth *pth);
void		ft_sleep(t_philo *philo, int i);

// void	*ft_philos(void *arg);

#endif
