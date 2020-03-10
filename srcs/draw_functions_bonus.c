/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/07 08:09:01 by rpet          #+#    #+#                 */
/*   Updated: 2020/03/10 09:45:25 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

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
		rgb = add_shades(rgb, mlx->ray.perpwalldist);
		put_pixel(cur_img, x, y, rgb);
		y++;
	}
}

/*
**		Main loop for drawing the main image.
*/

void			draw_main_image(t_data *mlx, int x, t_image *cur_img)
{
	int		y;
	int		rgb;

	y = 0;
	while (y < mlx->ray.draw_start)
	{
		rgb = add_shades(mlx->map.ceiling_rgb, (mlx->map.res.y / 2.0) /
				((mlx->map.res.y - y) - mlx->map.res.y / 2));
		put_pixel(cur_img, x, y, rgb);
		y++;
	}
	draw_texture(mlx, x, y, cur_img);
	y = mlx->ray.draw_end;
	while (y < mlx->map.res.y)
	{
		rgb = add_shades(mlx->map.floor_rgb, (mlx->map.res.y / 2.0) /
				(y - mlx->map.res.y / 2));
		put_pixel(cur_img, x, y, rgb);
		y++;
	}
}

/*
**		Draws and finds the coordinates of the sprite.
*/

void			draw_sprites(t_data *mlx, t_sprite *cur, t_image *cur_img,
		t_draw_sprite *spr)
{
	int				d;

	spr->draw.x = spr->draw_start.x;
	while (spr->draw.x < spr->draw_end.x)
	{
		spr->tex.x = (int)(256 * (spr->draw.x - (-spr->size / 2 + spr->screen))
				* cur->texture.w / spr->size) / 256;
		if (spr->transform.y > 0 &&
				spr->transform.y < mlx->ray.dis_buffer[spr->draw.x])
		{
			spr->draw.y = spr->draw_start.y;
			while (spr->draw.y < spr->draw_end.y)
			{
				d = spr->draw.y * 256 - mlx->map.res.y * 128 + spr->size * 128;
				spr->tex.y = ((d * cur->texture.h) / spr->size) / 256;
				spr->rgb = get_pixel(&cur->texture.img, spr->tex.x, spr->tex.y);
				spr->rgb = add_shades(spr->rgb, spr->transform.y);
				if (spr->rgb != 0)
					put_pixel(cur_img, spr->draw.x, spr->draw.y, spr->rgb);
				spr->draw.y++;
			}
		}
		spr->draw.x++;
	}
}
