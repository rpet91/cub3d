/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_frame.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/05 13:49:46 by rpet          #+#    #+#                 */
/*   Updated: 2020/02/27 17:25:12 by rpet          ########   odam.nl         */
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
	t_image	*cur_img;

	x = 0;
	cur_img = (mlx->active_img) ? &mlx->img1 : &mlx->img2;
	while (x < mlx->map.res.x)
	{
		calculate_variables(mlx, x);
		calculate_texture(mlx);
		sprite_engine(mlx);
		draw_image(mlx, x, cur_img);
		x++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, cur_img->img, 0, 0);
	mlx->active_img = !mlx->active_img;
	move_player(mlx);
	return (0);
}
