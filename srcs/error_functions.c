/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_functions.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/26 18:01:18 by rpet          #+#    #+#                 */
/*   Updated: 2020/03/10 16:08:37 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../cub3d.h"

void	error_message(char *str)
{
	ft_putstr_fd("Error\n", 1);
	ft_putendl_fd(str, 1);
	exit(1);
}

void	error_handling(char *str, t_data *mlx)
{
	destroy_textures(mlx);
	free_sprite_array(mlx);
	free_map(mlx);
	destroy_mlx(mlx);
	error_message(str);
}
