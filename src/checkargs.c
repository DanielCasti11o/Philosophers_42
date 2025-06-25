/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkargs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:29:59 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/06/25 16:00:43 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_str(char *arg, int argc)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (ft_isdigit(arg[i]) == 0 && arg[i] != '+')
			return (ft_error("ERROR: Invalid Argument 1!\n", 1), 0);
		i++;
	}
	if (ft_atol(arg) >= 2147483647)
		return (ft_error("ERROR: Invalid Argument 2!\n", 1), 0);
	return (1);
}

int	checkargs(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
		return (ft_error("N args invalid\n", 1), 0);
	while (argv[i])
	{
		if (!check_str(argv[i], argc))
			return (0);
		i++;
	}
	return (1);
}
