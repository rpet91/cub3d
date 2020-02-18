/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_frame.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/05 13:49:46 by rpet          #+#    #+#                 */
/*   Updated: 2020/02/11 08:11:32 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <mlx.h>
#include <math.h>

int		frame_loop(t_data *mlx)
{
	int		x;

	x = 0;
	while (x < MAX_X)
	{
		mlx->ray.cam_x = 2 * x / (double)MAX_X - 1;
		mlx->ray.raydir_x = mlx->pos.dir_x + mlx->pos.plane_x * mlx->ray.cam_x;
		mlx->ray.raydir_y = mlx->pos.dir_y + mlx->pos.plane_y * mlx->ray.cam_x;
		mlx->pos.map_x = (int)mlx->pos.pos_x;
		mlx->pos.map_y = (int)mlx->pos.pos_y;
		mlx->ray.deltadist_x = fabs(1 / mlx->ray.raydir_x);
		mlx->ray.deltadist_y = fabs(1 / mlx->ray.raydir_y);
		mlx->pos.hit = 0;
		if (mlx->ray.raydir_x < 0)
		{
			mlx->move.step_x = -1;
			mlx->ray.sidedist_x = (mlx->pos.pos_x - mlx->pos.map_x) *
				mlx->ray.deltadist_x;
		}
		else
		{
			mlx->move.step_x = 1;
			mlx->ray.sidedist_x = (mlx->pos.map_x + 1.0 - mlx->pos.pos_x) *
				mlx->ray.deltadist_x;
		}
		if (mlx->ray.raydir_y < 0)
		{
			mlx->move.step_y = -1;
			mlx->ray.sidedist_y = (mlx->pos.pos_y - mlx->pos.map_y) *
				mlx->ray.deltadist_y;
		}
		else
		{
			mlx->move.step_y = 1;
			mlx->ray.sidedist_y = (mlx->pos.map_y + 1.0 - mlx->pos.pos_y) *
				mlx->ray.deltadist_y;
		}
		while (mlx->pos.hit == 0)
		{
			if (mlx->ray.sidedist_x < mlx->ray.sidedist_y)
			{
				mlx->ray.sidedist_x += mlx->ray.deltadist_x;
				mlx->pos.map_x += mlx->move.step_x;
				mlx->pos.side = 0;
			}
			else
			{
				mlx->ray.sidedist_y += mlx->ray.deltadist_y;
				mlx->pos.map_y += mlx->move.step_y;
				mlx->pos.side = 1;
			}
			if (worldmap[mlx->pos.map_y][mlx->pos.map_x] > 0)
				mlx->pos.hit = 1;
		}
		if (mlx->pos.side == 0)
			mlx->ray.perpwalldist = (mlx->pos.map_x - mlx->pos.pos_x +
					(1 - mlx->move.step_x) / 2) / mlx->ray.raydir_x;
		else
			mlx->ray.perpwalldist =	(mlx->pos.map_y - mlx->pos.pos_y +
					(1 - mlx->move.step_y) / 2) / mlx->ray.raydir_y;
		mlx->pos.line_height = (int)(MAX_Y / mlx->ray.perpwalldist);
		mlx->pos.draw_start = -mlx->pos.line_height / 2 + MAX_Y / 2;
		if (mlx->pos.draw_start < 0)
			mlx->pos.draw_start = 0;
		mlx->pos.draw_end = mlx->pos.line_height / 2 + MAX_Y / 2;
		if (mlx->pos.draw_end >= MAX_Y)
			mlx->pos.draw_end = MAX_Y - 1;
		if (worldmap[mlx->pos.map_y][mlx->pos.map_x] == 1)
			mlx->color = 0xFF0000; //red
		else if (worldmap[mlx->pos.map_y][mlx->pos.map_x] == 2)
			mlx->color = 0x00FF00; //green
		else if (worldmap[mlx->pos.map_y][mlx->pos.map_x] == 3)
			mlx->color = 0x0000FF; //blue
		else if (worldmap[mlx->pos.map_y][mlx->pos.map_x] == 4)
			mlx->color = 0xF00FFF; //yellow
		else
			mlx->color = 0xFF00FF; //white
		if (mlx->pos.side == 1)
			mlx->color /= 2;
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
