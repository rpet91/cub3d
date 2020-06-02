/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_floors_bonus.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/11 10:30:11 by rpet          #+#    #+#                 */
/*   Updated: 2020/03/12 17:46:26 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

/*
**		Calculates the coordinates of the textures.
*/

void		floors_raycast(t_data *mlx, int y)
{
	t_ray		*ray;
	t_floor		*floor;
	int			max_x;
	int			max_y;

	ray = &mlx->ray;
	floor = &mlx->floor;
	max_x = mlx->map.res.x;
	max_y = mlx->map.res.y;
	floor->cur_p = y - max_y / 2;
	floor->row_dis = (double)(0.5 * max_y) / floor->cur_p;
	floor->step.x = floor->row_dis * (floor->ray2.x - floor->ray1.x) / max_x;
	floor->step.y = floor->row_dis * (floor->ray2.y - floor->ray1.y) / max_x;
	floor->pos.x = mlx->move.pos.x + floor->row_dis * floor->ray1.x;
	floor->pos.y = mlx->move.pos.y + floor->row_dis * floor->ray1.y;
}

/*
**		Finds the pixel color from the given texture.
*/

int			floor_rgb(t_data *mlx, int color, t_texture *tex, int y)
{
	t_floor		*floor;
	int			rgb;

	floor = &mlx->floor;
	if (color != -2)
		return (add_shades(color, mlx->map.res.y / (y / 2.0)));
	floor->t.x = (int)(tex->w * (floor->pos.x - floor->cell.x)) & (tex->w - 1);
	floor->t.y = (int)(tex->h * (floor->pos.y - floor->cell.y)) & (tex->h - 1);
	rgb = get_pixel(&tex->img, floor->t.x, floor->t.y);
	return (add_shades(rgb, mlx->map.res.y / (y / 2.0)));
}

void		calculate_ray_size(t_data *mlx)
{
	t_floor		*floor;
	t_ray		*ray;

	floor = &mlx->floor;
	ray = &mlx->ray;
	floor->ray1.x = ray->dir.x - ray->plane.x;
	floor->ray1.y = ray->dir.y - ray->plane.y;
	floor->ray2.x = ray->dir.x + ray->plane.x;
	floor->ray2.y = ray->dir.y + ray->plane.y;
}

void		draw_texture_pixel(t_data *mlx, t_image *cur_img, int y)
{
	int		rgb;
	int		x;

	x = 0;
	while (x < mlx->map.res.x)
	{
		mlx->floor.cell.x = (int)mlx->floor.pos.x;
		mlx->floor.cell.y = (int)mlx->floor.pos.y;
		mlx->floor.pos.x += mlx->floor.step.x;
		mlx->floor.pos.y += mlx->floor.step.y;
		rgb = floor_rgb(mlx, mlx->map.ceiling_rgb, &mlx->list_tex.ceiling, y);
		put_pixel(cur_img, x, mlx->map.res.y - y - 1, rgb);
		rgb = floor_rgb(mlx, mlx->map.floor_rgb, &mlx->list_tex.floor, y);
		put_pixel(cur_img, x, y, rgb);
		x++;
	}
}

void		draw_floors(t_data *mlx, t_image *cur_img)
{
	int		y;
	t_floor	*floor;

	floor = &mlx->floor;
	if (mlx->map.ceiling_rgb != -2 && mlx->map.floor_rgb != -2)
		return (draw_solid_floors(mlx, cur_img));
	calculate_ray_size(mlx);
	y = mlx->map.res.y - 1;
	while (y > mlx->map.res.y / 2 - 1)
	{
		floors_raycast(mlx, y);
		draw_texture_pixel(mlx, cur_img, y);
		y--;
	}
}
