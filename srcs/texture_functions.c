/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   texture_functions.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/25 08:09:08 by rpet          #+#    #+#                 */
/*   Updated: 2020/03/04 08:50:49 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include "../cub3d.h"

/*
**		Loads the correct texture for the correct side of the wall.
*/

t_texture	*get_texture_path(t_data *mlx)
{
	if (mlx->ray.side_hit == 0)
		return (&mlx->list_tex.north);
	else if (mlx->ray.side_hit == 2)
		return (&mlx->list_tex.south);
	else if (mlx->ray.side_hit == 1)
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

	cur_tex = get_texture_path(mlx);
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
**		Links the textures from the map with the list of textures.
*/

void		load_textures_from_map(t_data *mlx)
{
	mlx->list_tex.north.path = mlx->map.north_tex;
	mlx->list_tex.south.path = mlx->map.south_tex;
	mlx->list_tex.west.path = mlx->map.west_tex;
	mlx->list_tex.east.path = mlx->map.east_tex;
	mlx->list_tex.sprite.path = mlx->map.sprite_tex;
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
**		Creates an image for every available texture.
*/

void		texture_setup(t_data *mlx)
{
	int			i;
	t_list_tex	*tex;
	t_texture	*cur;

	i = 0;
	tex = &mlx->list_tex;
	load_textures_from_map(mlx);
	while (i < 5)
	{
		cur = select_texture_img(mlx, i);
		if (ft_strcmp(cur->path + ft_strlen(cur->path) - 4, ".png") == 0)
			cur->img.img = mlx_png_file_to_image(mlx->mlx, cur->path,
					&cur->w, &cur->h);
		else
			cur->img.img = mlx_xpm_file_to_image(mlx->mlx, cur->path,
					&cur->w, &cur->h);
		if (cur->img.img == NULL)
			error_handling(TEXTURE_ERROR, mlx);
		cur->img.addr = mlx_get_data_addr(cur->img.img,
			&cur->img.bits_per_pixel, &cur->img.line_length, &cur->img.endian);
		i++;
	}
}
