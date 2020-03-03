/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/07 08:09:01 by rpet          #+#    #+#                 */
/*   Updated: 2020/03/03 08:10:52 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
**		Returns a color value out of a texture coordinate.
*/

unsigned int	get_pixel(t_image *img, int x, int y)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(unsigned int*)dst);
}

/*
**		Places pixels in the image.
*/

void			put_pixel(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

/*
**		Loops through the texture and draws every pixel.
*/

void			draw_texture(t_data *mlx, int x, int y, t_image *cur_img)
{
	unsigned int	rgb;
	t_texture		*cur_tex;
	t_ray_tex		*ray;

	cur_tex = get_texture_path(mlx);
	ray = &mlx->ray_tex;
	while (y < mlx->ray.draw_end)
	{
		ray->tex.y = (int)ray->tex_pos & (cur_tex->h - 1);
		ray->tex_pos += ray->step;
		rgb = get_pixel(&cur_tex->img, ray->tex.x, ray->tex.y);
		put_pixel(cur_img, x, y, rgb);
		y++;
	}
}

/*
**		Main loop for drawing the image.
*/

void			draw_image(t_data *mlx, int x, t_image *cur_img)
{
	int		y;

	y = 0;
	while (y < mlx->ray.draw_start)
	{
		put_pixel(cur_img, x, y, mlx->map.ceiling_rgb);
		y++;
	}
	draw_texture(mlx, x, y, cur_img);
	y = mlx->ray.draw_end;
	while (y < mlx->map.res.y)
	{
		put_pixel(cur_img, x, y, mlx->map.floor_rgb);
		y++;
	}
}
