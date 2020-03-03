/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_frame.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/05 13:49:46 by rpet          #+#    #+#                 */
/*   Updated: 2020/03/03 10:51:34 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include "../cub3d.h"

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
		draw_main_image(mlx, x, cur_img);
		x++;
	}
	sprite_engine(mlx, cur_img);
	mlx_put_image_to_window(mlx->mlx, mlx->win, cur_img->img, 0, 0);
	mlx->active_img = !mlx->active_img;
	move_player(mlx);
	return (0);
}
