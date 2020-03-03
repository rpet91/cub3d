/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_sorting.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 09:34:50 by rpet          #+#    #+#                 */
/*   Updated: 2020/03/02 16:55:09 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub3d.h"
#include <stdlib.h>///

/*
**		Sorts the sprites from furthest to closest to the player.
*/

void	sort_sprites(t_data *mlx)
{
	t_sprite	**sprite;
	t_sprite	*temp;
	int			i;
	int			j;

	sprite = mlx->list.sprites;
	i = 1;
	while (i < mlx->list.amount)
	{
		j = i;
		while (j > 0)
		{
			if (sprite[j]->dis > sprite[j - 1]->dis)
			{
				temp = sprite[j - 1];
				sprite[j - 1] = sprite[j];
				sprite[j] = temp;
			}
			j--;
		}
		i++;
	}
}

/*
**		Calculates the distance to each sprite from the player's perspective.
*/

void	calculate_distances(t_data *mlx)
{
	t_sprite	**sprite;
	t_vector_d	pos;
	int			i;

	sprite = mlx->list.sprites;
	pos = mlx->move.pos;
	i = 0;
	while (i < mlx->list.amount)
	{
		sprite[i]->dis = pow(pos.x - sprite[i]->coords.x, 2) +
						pow(pos.y - sprite[i]->coords.y, 2);
		i++;
	}
}

void	sprite_engine(t_data *mlx, t_image *cur_img)
{
	t_sprite		*cur;
	t_draw_sprite	*spr;
	t_ray			*ray;
	unsigned int	rgb;
	int				i;
	int				d;

	calculate_distances(mlx);
	sort_sprites(mlx);
	spr = &mlx->draw_sprite;
	ray = &mlx->ray;
	i = 0;
	while (i < mlx->list.amount)
	{
		cur = mlx->list.sprites[i];
		spr->sprite.x = cur->coords.x - mlx->move.pos.x;
		spr->sprite.y = cur->coords.y - mlx->move.pos.y;
		spr->inv_det = 1.0 /
				(ray->plane.x * ray->dir.y - ray->dir.x * ray->plane.y);
		spr->transform.x = spr->inv_det * (ray->dir.y * spr->sprite.x -
				ray->dir.x * spr->sprite.y);
		spr->transform.y = spr->inv_det * (-ray->plane.y * spr->sprite.x +
				ray->plane.x * spr->sprite.y);
		spr->screen = (int)((mlx->map.res.x / 2) *
				(1 + spr->transform.x / spr->transform.y));
		spr->size = (int)fabs(mlx->map.res.y / spr->transform.y);

		spr->draw_start.y = -spr->size / 2 + mlx->map.res.y / 2;
		if (spr->draw_start.y < 0)
			spr->draw_start.y = 0;
		spr->draw_end.y = spr->size / 2 + mlx->map.res.y / 2;
		if (spr->draw_end.y >= mlx->map.res.y)
			spr->draw_end.y = mlx->map.res.y - 1;

		spr->draw_start.x = -spr->size / 2 + spr->screen;
		if (spr->draw_start.x < 0)
			spr->draw_start.x = 0;
		spr->draw_end.x = spr->size / 2 + spr->screen;
		if (spr->draw_end.x >= mlx->map.res.x)
			spr->draw_end.x = mlx->map.res.x - 1;

		spr->draw.x = spr->draw_start.x;
		while (spr->draw.x < spr->draw_end.x)
		{
			spr->tex.x = (int)(256 * (spr->draw.x - (-spr->size / 2 +
						spr->screen)) * cur->texture.w / spr->size) / 256;
			printf("trans y: [%f]\n", spr->transform.y);
			printf("dis_buffer: [%f]\n", ray->dis_buffer[spr->draw.x]);
			if (spr->transform.y > 0 &&
					spr->transform.y < ray->dis_buffer[spr->draw.x])
			{
				spr->draw.y = spr->draw_start.y;
				while (spr->draw.y < spr->draw_end.y)
				{
					d = spr->draw.y*256-mlx->map.res.y * 128 + spr->size * 128;
					spr->tex.y = ((d * cur->texture.h) / spr->size) / 256;
					printf("spr->tex x: [%i] y: [%i]\n", spr->tex.x, spr->tex.y);
					rgb = get_pixel(&cur->texture.img, spr->tex.x, spr->tex.y);
					printf("rgb: [%u]\n", rgb);
					if (rgb != 0)
						put_pixel(cur_img, spr->draw.x, spr->draw.y, rgb);
					spr->draw.y++;
				}
			}
			spr->draw.x++;
		}
		i++;
	}
}
