/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   texture_functions.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/25 08:09:08 by rpet          #+#    #+#                 */
/*   Updated: 2020/03/12 17:40:26 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include "../cub3d.h"

/*
**		Loads the correct texture for the correct side of the wall.
*/

t_texture	*get_wall_texture(t_data *mlx)
{
	if (mlx->ray.side_hit == 1)
		return (&mlx->list_tex.north);
	else if (mlx->ray.side_hit == 3)
		return (&mlx->list_tex.south);
	else if (mlx->ray.side_hit == 0)
		return (&mlx->list_tex.west);
	else
		return (&mlx->list_tex.east);
}

/*
**		Texture raycasting algorithm. Locates the texture.
*/

void		calculate_texture(t_data *mlx)
{
	t_texture	*cur_tex;
	t_ray		*ray;

	cur_tex = get_wall_texture(mlx);
	ray = &mlx->ray;
	if (ray->side_hit % 2 == 0)
		mlx->ray_tex.wall_x = mlx->move.pos.y + ray->perpwalldist * ray->ray.y;
	else
		mlx->ray_tex.wall_x = mlx->move.pos.x + ray->perpwalldist * ray->ray.x;
	mlx->ray_tex.wall_x -= floor(mlx->ray_tex.wall_x);
	if (ray->side_hit <= 1)
		mlx->ray_tex.wall_x = 1 - mlx->ray_tex.wall_x;
	mlx->ray_tex.tex.x = (int)(mlx->ray_tex.wall_x * (double)(cur_tex->w));
	mlx->ray_tex.step = 1.0 * cur_tex->h / ray->line_height;
	mlx->ray_tex.tex_pos = (ray->draw_start - mlx->map.res.y
			/ 2 + ray->line_height / 2) * mlx->ray_tex.step;
}

/*
**		Loops through all the available textures.
*/

t_texture	*select_texture_img(t_data *mlx, int i)
{
	if (i == 0)
		return (&mlx->list_tex.north);
	if (i == 1)
		return (&mlx->list_tex.south);
	if (i == 2)
		return (&mlx->list_tex.west);
	if (i == 3)
		return (&mlx->list_tex.east);
	else
		return (&mlx->list_tex.sprite);
}

/*
**		Converts texture to image.
*/

void		convert_to_image(t_data *mlx, t_texture *tex)
{
	if (ft_strcmp(tex->path + ft_strlen(tex->path) - 4, ".png") == 0)
		tex->img.img = mlx_png_file_to_image(mlx->mlx, tex->path,
				&tex->w, &tex->h);
	else
		tex->img.img = mlx_xpm_file_to_image(mlx->mlx, tex->path,
				&tex->w, &tex->h);
	if (tex->img.img == NULL)
		error_handling(TEXTURE_ERROR, mlx);
	tex->img.addr = mlx_get_data_addr(tex->img.img,
		&tex->img.bits_per_pixel, &tex->img.line_length, &tex->img.endian);
}

/*
**		Creates an image for every available texture.
*/

void		texture_setup(t_data *mlx)
{
	int			i;
	t_texture	*cur;

	mlx->list_tex.north.path = mlx->map.north_tex;
	mlx->list_tex.south.path = mlx->map.south_tex;
	mlx->list_tex.west.path = mlx->map.west_tex;
	mlx->list_tex.east.path = mlx->map.east_tex;
	mlx->list_tex.sprite.path = mlx->map.sprite_tex;
	mlx->list_tex.floor.path = mlx->map.floor_tex;
	mlx->list_tex.ceiling.path = mlx->map.ceiling_tex;
	i = 0;
	while (i < 7)
	{
		if (i < 5)
			cur = select_texture_img(mlx, i);
		if (i == 5 && mlx->map.floor_rgb == -2)
			cur = &mlx->list_tex.floor;
		if (i == 6 && mlx->map.ceiling_rgb == -2)
			cur = &mlx->list_tex.ceiling;
		convert_to_image(mlx, cur);
		i++;
	}
}
