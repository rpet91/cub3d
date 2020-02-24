/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/07 08:09:01 by rpet          #+#    #+#                 */
/*   Updated: 2020/02/24 15:39:03 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*check_texture(t_data *mlx)
{
	if (mlx->ray.side_hit == 1)
		mlx->texture == mlx->map.north_tex;
	else if (mlx->ray.side_hit == 2)
		mlx->texture == mlx->map.south_tex;
	else if (mlx->ray.side_hit == 3)
		mlx->texture == mlx->map.west_tex;
	else if (mlx->ray.side_hit == 4)
		mlx->texture == mlx->map.east_tex;
	return (mlx->texture);
}

void	put_pixel(t_image *img, int x, int y, int color)
{
	char    *dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(int*)dst = color;
}

int		draw_image(t_data *mlx, int x)
{
	int		y;

	y = 0;
	//printf("x: [%f], y: [%f]\n", mlx->move.pos.x, mlx->move.pos.y);
	//printf("start: [%i] end: [%i]\n", mlx->ray.draw_start, mlx->ray.draw_end);
	while (y < mlx->ray.draw_start)
	{
		if (mlx->active_img == 1)
			put_pixel(&mlx->img1, x, y, mlx->map.ceiling_rgb);
		else
			put_pixel(&mlx->img2, x, y, mlx->map.ceiling_rgb);
		y++;
	}
	while (y <= mlx->ray.draw_end)
	{
		if (mlx->active_img == 1)
			put_pixel(&mlx->img1, x, y, mlx->color);
		else
			put_pixel(&mlx->img2, x, y, mlx->color);
		y++;
	}
	while (y < mlx->map.res.y)
	{
		if (mlx->active_img == 1)
			put_pixel(&mlx->img1, x, y, mlx->map.floor_rgb);
		else
			put_pixel(&mlx->img2, x, y, mlx->map.floor_rgb);
		y++;
	}
	return (0);
}
