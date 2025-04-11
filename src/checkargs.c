/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkargs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:29:59 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/04/10 12:40:40 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void    check_str(char *arg)
{
	int i;

	i = 0;
	while (arg[i])
	{
		if (ft_isdigit(arg[i]) == 0)
			ft_error("ERROR: Invalid Argument!\n", 1);
		i++;
	}
	if (i >= 11)
		ft_error("ERROR: Invalid Argument!\n", 1);
}

void   checkargs(int argc, char **argv)
 {
	int i;

	i = 0;
	if (argc < 5 || argc > 6)
		ft_error("N args invalid\n", 1);
	while (argv[i])
	{
		check_str(argv[i]);
		i++;
	}
 }
