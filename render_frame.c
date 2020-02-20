/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_frame.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/05 13:49:46 by rpet          #+#    #+#                 */
/*   Updated: 2020/02/20 13:51:01 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <mlx.h>
#include <math.h>

int		frame_loop(t_data *mlx)
{
	int		x;

	x = 0;
	while (x < mlx->map.res.x)
	{
		mlx->ray.cam_x = 2 * x / (double)mlx->map.res.x - 1;
		mlx->ray.ray.x = mlx->ray.dir.x + mlx->ray.plane.x * mlx->ray.cam_x;
		mlx->ray.ray.y = mlx->ray.dir.y + mlx->ray.plane.y * mlx->ray.cam_x;
		mlx->ray.map.x = (int)mlx->ray.pos.x;
		mlx->ray.map.y = (int)mlx->ray.pos.y;
		mlx->ray.delta.x = fabs(1 / mlx->ray.ray.x);
		mlx->ray.delta.y = fabs(1 / mlx->ray.ray.y);
		mlx->ray.hit = 0;
		if (mlx->ray.ray.x < 0)
		{
			mlx->move.step.x = -1;
			mlx->ray.side.x = (mlx->ray.pos.x - mlx->ray.map.x) *
				mlx->ray.delta.x;
		}
		else
		{
			mlx->move.step.x = 1;
			mlx->ray.side.x = (mlx->ray.map.x + 1.0 - mlx->ray.pos.x) *
				mlx->ray.delta.x;
		}
		if (mlx->ray.ray.y < 0)
		{
			mlx->move.step.y = -1;
			mlx->ray.side.y = (mlx->ray.pos.y - mlx->ray.map.y) *
				mlx->ray.delta.y;
		}
		else
		{
			mlx->move.step.y = 1;
			mlx->ray.side.y = (mlx->ray.map.y + 1.0 - mlx->ray.pos.y) *
				mlx->ray.delta.y;
		}
		while (mlx->ray.hit == 0)
		{
			if (mlx->ray.side.x < mlx->ray.side.y)
			{
				mlx->ray.side.x += mlx->ray.delta.x;
				mlx->ray.map.x += mlx->move.step.x;
				mlx->ray.part = 0;
			}
			else
			{
				mlx->ray.side.y += mlx->ray.delta.y;
				mlx->ray.map.y += mlx->move.step.y;
				mlx->ray.part = 1;
			}
		//	if (mlx->map.map[mlx->pos.map_y][mlx->pos.map_x] > 0)
			if (worldmap[mlx->ray.map.y][mlx->ray.map.x] > 0)
				mlx->ray.hit = 1;
		}
		if (mlx->ray.part == 0)
			mlx->ray.perpwalldist = (mlx->ray.map.x - mlx->ray.pos.x +
					(1 - mlx->move.step.x) / 2) / mlx->ray.ray.x;
		else
			mlx->ray.perpwalldist =	(mlx->ray.map.y - mlx->ray.pos.y +
					(1 - mlx->move.step.y) / 2) / mlx->ray.ray.y;
		mlx->ray.line_height = (int)(mlx->map.res.y / mlx->ray.perpwalldist);
		mlx->ray.draw_start = -mlx->ray.line_height / 2 + mlx->map.res.y / 2;
		if (mlx->ray.draw_start < 0)
			mlx->ray.draw_start = 0;
		mlx->ray.draw_end = mlx->ray.line_height / 2 + mlx->map.res.y / 2;
		if (mlx->ray.draw_end >= mlx->map.res.y)
			mlx->ray.draw_end = mlx->map.res.y - 1;
	//	if (mlx->map.map[mlx->pos.map_y][mlx->pos.map_x] == 1)
		if (worldmap[mlx->ray.map.y][mlx->ray.map.x] == 1)
			mlx->color = 0xFF0000; //red
		else if (worldmap[mlx->ray.map.y][mlx->ray.map.x] == 2)
			mlx->color = 0x00FF00; //green
		else if (worldmap[mlx->ray.map.y][mlx->ray.map.x] == 3)
			mlx->color = 0x0000FF; //blue
		else if (worldmap[mlx->ray.map.y][mlx->ray.map.x] == 4)
			mlx->color = 0xF00FFF; //yellow
		else
			mlx->color = 0xFF00FF; //white
		if (mlx->ray.part == 1)
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
