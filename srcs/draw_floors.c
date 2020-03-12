/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_floors.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/11 10:30:11 by rpet          #+#    #+#                 */
/*   Updated: 2020/03/11 13:15:30 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
**		Draws the floors a solid color.
*/

void	draw_floors(t_data *mlx, t_image *cur_img)
{
	draw_solid_floors(mlx, cur_img);
}
