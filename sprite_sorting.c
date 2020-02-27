/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_sorting.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 09:34:50 by rpet          #+#    #+#                 */
/*   Updated: 2020/02/27 17:56:55 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "cub3d.h"

void	sort_sprites(t_data *mlx)
{
	t_sprite	**sprite;
	t_sprite	*temp;
	int			i;
	int			j;

	sprite = mlx->list.sprite;
	i = 1;
	while (i < mlx->list.amount)
	{
		j = i;
		while (sprite[j]->dis > sprite[j - 1]->dis && j - 1 >= 0)
		{
			temp = sprite[j - 1];
			sprite[j] = sprite[j - 1];
			sprite[j] = temp;
			j--;
		}
		i++;
	}
}

void	calculate_distance(t_data *mlx)
{
	t_sprite	**sprite;
	t_vector_d	*pos;
	int			i;

	sprite = mlx->list.sprite;
	pos = &mlx->move.pos;
	i = 0;
	while (i < mlx->list.amount)
	{
		sprite[i]->dis = pow(pos->x - sprite[i]->coords.x, 2) +
						pow(pos->y - sprite[i]->coords.y, 2);
		printf("distance to player: [%f]\n", sprite[i]->dis);
		i++;
	}
	printf("\n");
}

void	sprite_engine(t_data *mlx)
{
	calculate_distance(mlx);
	sort_sprites(mlx);
	int i = 0;
	while (i < mlx->list.amount)
	{
		printf("sorted distance: [%f]\n", mlx->list.sprite[i]->dis);
		i++;
	}
	exit(1);
}
