/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_setup.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 10:58:07 by rpet          #+#    #+#                 */
/*   Updated: 2020/03/03 16:46:59 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../cub3d.h"

/*
**		Adds the new sprite to the array of sprites.
*/

t_sprite	**add_sprite_to_array(t_data *mlx, t_sprite *new_sprite)
{
	t_sprite	**sprites;
	int			i;

	sprites = malloc(sizeof(t_sprite *) * (mlx->list.amount + 1));
	if (sprites == NULL)
		error_handling(MALLOC, mlx);
	i = 0;
	while (i < mlx->list.amount)
	{
		sprites[i] = mlx->list.sprites[i];
		i++;
	}
	sprites[i] = new_sprite;
	free(mlx->list.sprites);
	return (sprites);
}

/*
**		Creates a new sprite and saves the exact coords.
*/

t_sprite	*create_new_sprite(t_data *mlx, int y, int x)
{
	t_sprite	*new_sprite;

	new_sprite = malloc(sizeof(t_sprite));
	if (new_sprite == NULL)
		error_handling(MALLOC, mlx);
	new_sprite->coords.y = y + 0.5;
	new_sprite->coords.x = x + 0.5;
	new_sprite->texture = mlx->list_tex.sprite;
	return (new_sprite);
}

/*
**		Loops through the map. Adds the sprite to the struct when found.
*/

void		locate_sprites(t_data *mlx)
{
	t_sprite	*sprite;
	int			y;
	int			x;

	y = 0;
	while (mlx->map.map[y])
	{
		x = 0;
		while (mlx->map.map[y][x])
		{
			if (mlx->map.map[y][x] == '2')
			{
				sprite = create_new_sprite(mlx, y, x);
				mlx->list.sprites = add_sprite_to_array(mlx, sprite);
				mlx->list.amount++;
			}
			x++;
		}
		y++;
	}
}

/*
**		Main functions for sprites setup.
*/

void		sprite_setup(t_data *mlx)
{
	mlx->list.sprites = malloc(sizeof(t_sprite *));
	if (mlx->list.sprites == NULL)
		error_handling(MALLOC, mlx);
	mlx->list.sprites[0] = NULL;
	locate_sprites(mlx);
}
