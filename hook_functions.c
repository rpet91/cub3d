/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hook_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/05 15:25:20 by rpet          #+#    #+#                 */
/*   Updated: 2020/02/05 15:45:30 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>
#include <mlx.h>

int		close_window(t_data *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->win);
	exit(0);
	return (0);
}

int		key_press(int keycode, t_data *mlx)
{
	printf("%i\n", keycode);
	if (keycode == ESC_BUTTON)
		close_window(mlx);
	if (keycode == KEY_W)
		mlx->move.w = 1;
	if (keycode == KEY_S)
		mlx->move.s = 1;
	if (keycode == KEY_A)
		mlx->move.a = 1;
	if (keycode == KEY_D)
		mlx->move.d = 1;
	if (keycode == KEY_LEFT)
		mlx->move.left = 1;
	if (keycode == KEY_RIGHT)
		mlx->move.right = 1;
	return (0);
}

int		key_release(int keycode, t_data *mlx)
{
	if (keycode == KEY_W)
		mlx->move.w = 0;
	if (keycode == KEY_S)
		mlx->move.s = 0;
	if (keycode == KEY_A)
		mlx->move.a = 0;
	if (keycode == KEY_D)
		mlx->move.d = 0;
	if (keycode == KEY_LEFT)
		mlx->move.left = 0;
	if (keycode == KEY_RIGHT)
		mlx->move.right = 0;
	return (0);
}
