/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/24 09:46:50 by rpet          #+#    #+#                 */
/*   Updated: 2020/01/30 18:06:54 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "cub3d.h"
#include <stdlib.h>
#include <stdio.h> //norm

# define MAX_X 600
# define MAX_Y 600

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	create_image(t_data *mlx)
{
	int		x;
	int		y;
	int		radius;
	double	color1;
	double	color2;
	double	color3;

	x = 0;
	y = 0;
	radius = 50;
	color1 = 0x00000000;
	color2 = 0x0000FF00;
	color3 = 0;
	while (y < MAX_Y)
	{
		while (x < MAX_X)
		{
			my_mlx_pixel_put(mlx->img, x, y, 0);
			x++;
		}
		x = 0;
		y++;
	}
	x = -radius;
	y = -radius;
	while (y <= radius)
	{
		while (x <= radius)
		{
			if (x*x + y*y < radius*radius+radius)
			{
				color3 = (color1 + color2 * (double)y / (double)(2*radius));
				my_mlx_pixel_put(mlx->img, mlx->x + (50 - x), mlx->y + (50 + y), color3);
				my_mlx_pixel_put(mlx->img, mlx->x + (50 + x), mlx->y + (50 - y), color3);
			}
			x++;
		}
		x = -radius;
		y++;
	}
}

int		close_window(t_data *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->mlx_win);
	exit (0);
	return (0);
}

int		key_press(int keycode, t_data *mlx)
{
	printf("%i\n", keycode);
	if (keycode == ESC_BUTTON)
		close_window(mlx);
	if (keycode == KEY_W)
		mlx->move->w = 1;
	if (keycode == KEY_S)
		mlx->move->s = 1;
	if (keycode == KEY_A)
		mlx->move->a = 1;
	if (keycode == KEY_D)
		mlx->move->d = 1;
	return (0);
}

int		key_release(int keycode, t_data *mlx)
{
	if (keycode == KEY_W)
		mlx->move->w = 0;
	if (keycode == KEY_S)
		mlx->move->s = 0;
	if (keycode == KEY_A)
		mlx->move->a = 0;
	if (keycode == KEY_D)
		mlx->move->d = 0;
	return (0);
}

int		render_frame(t_data *mlx)
{
	if (mlx->move->w == 1)
		mlx->y -= (mlx->y - 10 >= 0) ? 10 : mlx->y;
	if (mlx->move->s == 1)
		mlx->y += (mlx->y + 10 <= 500) ? 10 : 500 - mlx->y;
	if (mlx->move->a == 1)
		mlx->x -= (mlx->x - 10 >= 0) ? 10 : mlx->x;
	if (mlx->move->d == 1)
		mlx->x += (mlx->x + 10 <= 500) ? 10 : 500 - mlx->x;
	if (mlx->move->w == 1 || mlx->move->s == 1 || mlx->move->a == 1 ||
			mlx->move->d == 1)
	{
		create_image(mlx);
		mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->img->img, 0, 0);
	}
	return (0);
}

int		mouse_trace(int x, int y)
{
	if (x >= 0 && x <= MAX_X && y >= 0 && y <= MAX_Y)
		printf("[%i] - [%i]\n", x, y);
	return (0);
}

int		main(void)
{
	t_move		move;
	t_image		img;
	t_data		mlx;

	mlx.mlx = mlx_init();
	mlx.mlx_win = mlx_new_window(mlx.mlx, MAX_X, MAX_Y, "rpet's game");
	img.img = mlx_new_image(mlx.mlx, MAX_X, MAX_Y);
	mlx.img = &img;
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	mlx.x = 0;
	mlx.y = 0;
	mlx.move = &move;
	create_image(&mlx);
	mlx_put_image_to_window(mlx.mlx, mlx.mlx_win, img.img, 0, 0);
	mlx_hook(mlx.mlx_win, 2, 1L<<0, key_press, &mlx);
	mlx_hook(mlx.mlx_win, 3, 1L<<1, key_release, &mlx);
	mlx_hook(mlx.mlx_win, 6, 1L<<6, mouse_trace, &mlx);
	mlx_hook(mlx.mlx_win, 17, 1L<<17, close_window, &mlx);
	mlx_loop_hook(mlx.mlx, render_frame, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
