/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:01:43 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/06/26 02:35:58 by daniel-cast      ###   ########.fr       */
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
	unsigned long	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	eat_required; // comidas requeridas para acabar
	pthread_mutex_t	*forks; // array de mutexes para los tenedores
	unsigned int	end_sim;
	bool			dead_flag;
	long			start_time;
	int				eat_fin;
	pthread_mutex_t	printfs;
	pthread_mutex_t	lock_data;
	pthread_mutex_t	stop;
}	t_datash;

typedef struct s_philo
{
	int				id; // identify
	pthread_t		thread;
	long			last_eat;
	pthread_mutex_t	*right_fk; // tenedores
	pthread_mutex_t	*left_fk;
	t_datash		*data;
	int				eat;
	bool			is_dead;

}	t_philo;

typedef struct s_pth
{
	t_datash	*data;
	t_philo		*philos;
	int			n_threads;
}	t_pth;

enum
{
	EAT,
	SLEEP,
	DIED,
	DIED_FLAG,
	THINK,
	FORK,
	FORKS
};

int			ft_atol(const char *nptr);
int			ft_atoui(const char *nptr);
int			ft_error(char *msg, int f);
int			check_str(char *arg, int argc);
int			checkargs(int argc, char **argv);
t_pth		*init_struct(char **argv);
t_datash	*init_data(char **argv);
void		util_init_data(t_datash *data, char **argv);
t_philo		*init_philos(t_datash *data);
void		prepare_routine(t_pth *pth);
void		*do_routine(void *arg);
int			take_forks(t_philo *philo);
void		*monitor_keep(void *arg);
int			ft_sleep(t_philo *philo);
long		get_time(void);
void		ft_usleep(long start, long end, t_philo *philo);
int			time_over(long actual, t_philo *philo);
int			exit_to_program(t_philo *philo);
int			someone_died(t_philo *philo);
int			case_one_philo(t_philo *philo);
int			handle_mutex_forks(t_philo *philo);
void		new_last_meal(t_philo *philo);
void		joins_threads(t_pth *pth);
int			check_death(t_philo *philo, int i);
int			update_meal(t_philo *philo);
int			handle_stop(t_datash *data, t_philo *philo);

// FREE
void		free_pth(t_pth *pth);
void		free_data(t_datash *data);
void		free_forks(pthread_mutex_t *forks, int n);
void		destroys(t_datash *data);

// UTILS WITH MACROS
void		printf_mutex(t_philo *philo, int action);
void		action_mutex(t_philo *philo, int action);
// void	*ft_philos(void *arg);

#endif
