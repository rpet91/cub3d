/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycasting.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/21 16:52:56 by rpet          #+#    #+#                 */
/*   Updated: 2020/03/03 09:22:10 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../cub3d.h"

/*
**		Calculates the draw coordinates & which texture.
*/

void	check_draw_coords(t_data *mlx)
{
	t_ray	*ray;

	ray = &mlx->ray;
	ray->line_height = (int)(mlx->map.res.y / ray->perpwalldist);
	ray->draw_start = -ray->line_height / 2 + mlx->map.res.y / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + mlx->map.res.y / 2;
	if (ray->draw_end >= mlx->map.res.y)
		ray->draw_end = mlx->map.res.y - 1;
	if (ray->side_hit == 0)
		ray->side_hit = (ray->ray.x > 0) ? 0 : 2;
	else
		ray->side_hit = (ray->ray.y > 0) ? 1 : 3;
}

/*
**		Calculates the distance to a wall.
*/

void	calculate_wall_distance(t_data *mlx, int x)
{
	t_ray	*ray;

	ray = &mlx->ray;
	if (ray->side_hit == 0)
		ray->perpwalldist = (ray->map.x - mlx->move.pos.x +
		(1 - ray->step.x) / 2) / ray->ray.x;
	else
		ray->perpwalldist = (ray->map.y - mlx->move.pos.y +
		(1 - ray->step.y) / 2) / ray->ray.y;
	ray->dis_buffer[x] = ray->perpwalldist;
}

/*
**		Calculates when a wall is hit.
*/

void	check_wall_hit(t_data *mlx)
{
	t_ray	*ray;

	ray = &mlx->ray;
	if (ray->side.x < ray->side.y)
	{
		ray->side.x += ray->delta.x;
		ray->map.x += ray->step.x;
		ray->side_hit = 0;
	}
	else
	{
		ray->side.y += ray->delta.y;
		ray->map.y += ray->step.y;
		ray->side_hit = 1;
	}
	if (mlx->map.map[ray->map.y][ray->map.x] == '1')
		ray->hit = 1;
}

/*
**		Checks what direction the player is looking at.
*/

void	check_player_direction(t_data *mlx)
{
	t_ray	*ray;

	ray = &mlx->ray;
	if (ray->ray.x < 0)
	{
		ray->step.x = -1;
		ray->side.x = (mlx->move.pos.x - ray->map.x) * ray->delta.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side.x = (ray->map.x + 1.0 - mlx->move.pos.x) * ray->delta.x;
	}
	if (ray->ray.y < 0)
	{
		ray->step.y = -1;
		ray->side.y = (mlx->move.pos.y - ray->map.y) * ray->delta.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side.y = (ray->map.y + 1.0 - mlx->move.pos.y) * ray->delta.y;
	}
}

/*
**		Determines where to start the raycast.
*/

void	calculate_variables(t_data *mlx, int x)
{
	t_ray	*ray;

	ray = &mlx->ray;
	ray->cam_x = 2 * x / (double)mlx->map.res.x - 1;
	ray->ray.x = ray->dir.x + ray->plane.x * ray->cam_x;
	ray->ray.y = ray->dir.y + ray->plane.y * ray->cam_x;
	ray->map.x = (int)mlx->move.pos.x;
	ray->map.y = (int)mlx->move.pos.y;
	ray->delta.x = fabs(1 / ray->ray.x);
	ray->delta.y = fabs(1 / ray->ray.y);
	ray->hit = 0;
	check_player_direction(mlx);
	while (mlx->ray.hit == 0)
		check_wall_hit(mlx);
	calculate_wall_distance(mlx, x);
	check_draw_coords(mlx);
}
