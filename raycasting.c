/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycasting.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/21 16:52:56 by rpet          #+#    #+#                 */
/*   Updated: 2020/02/26 09:31:28 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub3d.h"

/*
**		Calculates the draw coordinates & which texture.
*/

void	check_draw(t_data *mlx)
{
	mlx->ray.line_height = (int)(mlx->map.res.y / mlx->ray.perpwalldist);
	mlx->ray.draw_start = -mlx->ray.line_height / 2 + mlx->map.res.y / 2;
	if (mlx->ray.draw_start < 0)
		mlx->ray.draw_start = 0;
	mlx->ray.draw_end = mlx->ray.line_height / 2 + mlx->map.res.y / 2;
	if (mlx->ray.draw_end >= mlx->map.res.y)
		mlx->ray.draw_end = mlx->map.res.y - 1;
	if (mlx->ray.side_hit == 0)
		mlx->ray.side_hit = (mlx->ray.ray.x > 0) ? 0 : 2;
	else
		mlx->ray.side_hit = (mlx->ray.ray.y > 0) ? 1 : 3;
}

/*
**		Calculates distance to wall.
*/

void	check_wall_hit(t_data *mlx)
{
	if (mlx->ray.side.x < mlx->ray.side.y)
	{
		mlx->ray.side.x += mlx->ray.delta.x;
		mlx->ray.map.x += mlx->ray.step.x;
		mlx->ray.side_hit = 0;
	}
	else
	{
		mlx->ray.side.y += mlx->ray.delta.y;
		mlx->ray.map.y += mlx->ray.step.y;
		mlx->ray.side_hit = 1;
	}
	if (mlx->map.map[mlx->ray.map.y][mlx->ray.map.x] > '0')
		mlx->ray.hit = 1;
	if (mlx->ray.side_hit == 0)
		mlx->ray.perpwalldist = (mlx->ray.map.x - mlx->move.pos.x +
		(1 - mlx->ray.step.x) / 2) / mlx->ray.ray.x;
	else
		mlx->ray.perpwalldist = (mlx->ray.map.y - mlx->move.pos.y +
		(1 - mlx->ray.step.y) / 2) / mlx->ray.ray.y;
}

/*
**		Checks what direction the player is looking at.
*/

void	check_player_direction(t_data *mlx)
{
	if (mlx->ray.ray.x < 0)
	{
		mlx->ray.step.x = -1;
		mlx->ray.side.x = (mlx->move.pos.x - mlx->ray.map.x) *
			mlx->ray.delta.x;
	}
	else
	{
		mlx->ray.step.x = 1;
		mlx->ray.side.x = (mlx->ray.map.x + 1.0 - mlx->move.pos.x) *
			mlx->ray.delta.x;
	}
	if (mlx->ray.ray.y < 0)
	{
		mlx->ray.step.y = -1;
		mlx->ray.side.y = (mlx->move.pos.y - mlx->ray.map.y) *
			mlx->ray.delta.y;
	}
	else
	{
		mlx->ray.step.y = 1;
		mlx->ray.side.y = (mlx->ray.map.y + 1.0 - mlx->move.pos.y) *
			mlx->ray.delta.y;
	}
}

/*
**		Determines where to start the raycast.
*/

void	calculate_variables(t_data *mlx, int x)
{
	mlx->ray.cam_x = 2 * x / (double)mlx->map.res.x - 1;
	mlx->ray.ray.x = mlx->ray.dir.x + mlx->ray.plane.x * mlx->ray.cam_x;
	mlx->ray.ray.y = mlx->ray.dir.y + mlx->ray.plane.y * mlx->ray.cam_x;
	mlx->ray.map.x = (int)mlx->move.pos.x;
	mlx->ray.map.y = (int)mlx->move.pos.y;
	mlx->ray.delta.x = fabs(1 / mlx->ray.ray.x);
	mlx->ray.delta.y = fabs(1 / mlx->ray.ray.y);
	mlx->ray.hit = 0;
	check_player_direction(mlx);
	while (mlx->ray.hit == 0)
		check_wall_hit(mlx);
	check_draw(mlx);
}
