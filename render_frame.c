/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_frame.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/05 13:49:46 by rpet          #+#    #+#                 */
/*   Updated: 2020/02/24 14:47:02 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <mlx.h>
#include <math.h>

/*
**		Constantly checks, calculates and draws the game.
*/

int		frame_loop(t_data *mlx)
{
	int		x;

	x = 0;
	while (x < mlx->map.res.x)
	{
		calculate_variables(mlx, x);
		if (mlx->map.map[mlx->ray.map.y][mlx->ray.map.x] == '1')
			mlx->texture = check_texture(mlx); //0xFF0000; //red
		else
			mlx->color = 0xFFFF00;
		draw_image(mlx, x);
		x++;
	}
	if (mlx->active_img == 1)
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img1.img, 0, 0);
	else
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img2.img, 0, 0);
	mlx->active_img = !mlx->active_img;
	move_player(mlx);
	return (0);
}
