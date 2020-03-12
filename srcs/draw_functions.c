/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/07 08:09:01 by rpet          #+#    #+#                 */
/*   Updated: 2020/03/12 15:44:58 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
**		Draws the floor and ceiling colors when both solid.
*/

void			draw_solid_floors(t_data *mlx, t_image *cur_img)
{
	int		map_y;
	int		y;
	int		x;
	int		rgb_c;
	int		rgb_f;

	map_y = mlx->map.res.y;
	y = 0;
	while (y < map_y / 2)
	{
		rgb_c = add_shades(mlx->map.ceiling_rgb, (map_y / 2.0) / y);
		rgb_f = add_shades(mlx->map.floor_rgb, (map_y / 2.0) / y);
		x = 0;
		while (x < mlx->map.res.x)
		{
			put_pixel(cur_img, x, (map_y / 2) - y, rgb_c);
			put_pixel(cur_img, x, (map_y / 2) + y, rgb_f);
			x++;
		}
		y++;
	}
}

/*
**		Loops through the texture and draws every pixel.
*/

void			draw_wall_texture(t_data *mlx, int x, t_image *cur_img)
{
	int				y;
	unsigned int	rgb;
	t_texture		*cur_tex;
	t_ray_tex		*ray;

	cur_tex = get_wall_texture(mlx);
	ray = &mlx->ray_tex;
	y = mlx->ray.draw_start;
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
