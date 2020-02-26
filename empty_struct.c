/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   empty_struct.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/21 08:31:00 by rpet          #+#    #+#                 */
/*   Updated: 2020/02/26 15:08:13 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cub3d.h"

/*
**		Creates a new map with every value set to zero.
*/

void	create_empty_map(t_map *map)
{
	map->player.x = 0;
	map->player.y = 0;
	map->res.x = 0;
	map->res.y = 0;
	map->size.x = 0;
	map->size.y = 0;
	map->line = 0;
	map->north_tex = 0;
	map->south_tex = 0;
	map->west_tex = 0;
	map->east_tex = 0;
	map->sprite_tex = 0;
	map->floor_rgb = -1;
	map->ceiling_rgb = -1;
	map->check = 0;
	map->map = malloc(sizeof(char *));
	if (map->map == NULL)
		return ;
	map->map[0] = NULL;
}
