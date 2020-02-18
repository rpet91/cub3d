/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handling.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/07 09:36:39 by rpet          #+#    #+#                 */
/*   Updated: 2020/02/07 10:04:59 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

void	error_handling(char *str)
{
	ft_putstr_fd("Error\n", 1);
	ft_putstr_fd(str, 1);
	ft_putstr_fd("\n", 1);
	exit(1);
}
