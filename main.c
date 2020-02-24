/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/24 09:46:50 by rpet          #+#    #+#                 */
/*   Updated: 2020/02/24 09:55:18 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "cub3d.h"
#include <stdlib.h>

/*
**		Locates what direction the player faces to and sets starting position.
*/

void	starting_face_direction(t_data *mlx, int y, int x)
{
	if (mlx->map.map[y][x] == 'N' || mlx->map.map[y][x] == 'S')
	{
		mlx->ray.dir.x = 0;
		mlx->ray.plane.y = 0;
		mlx->ray.dir.y = (mlx->map.map[y][x] == 'N') ? -1 : 1;
		mlx->ray.plane.x = (mlx->map.map[y][x] == 'N') ? 0.66 : -0.66;
	}
	else if (mlx->map.map[y][x] == 'W' || mlx->map.map[y][x] == 'E')
	{
		mlx->ray.dir.y = 0;
		mlx->ray.plane.x = 0;
		mlx->ray.dir.x = (mlx->map.map[y][x] == 'W') ? -1 : 1;
		mlx->ray.plane.y = (mlx->map.map[y][x] == 'W') ? -0.66 : 0.66;
	}
	mlx->move.pos.y = y;
	mlx->move.pos.x = x;
	mlx->map.map[y][x] = '0';
}

/*
**		Adjusts the given resolution if necessary.
*/

void	get_correct_window_resolution(t_data *mlx)
{
	int		max_x;
	int		max_y;

	mlx_get_screen_size(&mlx, &max_x, &max_y);
	if (mlx->map.res.x > max_x)
		mlx->map.res.x = max_x;
	if (mlx->map.res.y > max_y)
		mlx->map.res.y = max_y;
}

/*
**		The basic setup of the game.
*/

int		mlx_setup(t_data *mlx)
{
	mlx->mlx = mlx_init();
	if (mlx->mlx == NULL)
		return (error_handling(MLX_ERROR));
	get_correct_window_resolution(mlx);
	mlx->win = mlx_new_window(mlx->mlx, mlx->map.res.x, mlx->map.res.y, "GAME");
	if (mlx->win == NULL)
		return (error_handling(MLX_ERROR));
	mlx->img1.img = mlx_new_image(mlx->mlx, mlx->map.res.x, mlx->map.res.y);
	mlx->img2.img = mlx_new_image(mlx->mlx, mlx->map.res.x, mlx->map.res.y);
	if (mlx->img1.img == NULL || mlx->img2.img == NULL)
		return (error_handling(MLX_ERROR));
	mlx->img1.addr = mlx_get_data_addr(mlx->img1.img,
		&mlx->img1.bits_per_pixel, &mlx->img1.line_length, &mlx->img1.endian);
	mlx->img2.addr = mlx_get_data_addr(mlx->img2.img,
		&mlx->img2.bits_per_pixel, &mlx->img2.line_length, &mlx->img2.endian);
	mlx->active_img = 1;
	starting_face_direction(mlx, mlx->map.player.y, mlx->map.player.x);
	return (0);
}

int		main(int argc, char **argv)
{
	t_data		mlx;
	t_map		map;
	int			error;

	if (argc <= 0)
		return (0);
	error = parse_map(&map, argv[1]);
	if (error == -1)
		return (-1);
	mlx.map = map;
	error = mlx_setup(&mlx);
	if (error == -1)
		return (-1);
	mlx_hook(mlx.win, 2, 0, key_press, &mlx);
	mlx_hook(mlx.win, 3, 1L << 1, key_release, &mlx);
	mlx_hook(mlx.win, 17, 1L << 17, close_window, &mlx);
	mlx_do_key_autorepeatoff(mlx.mlx);
	mlx_loop_hook(mlx.mlx, frame_loop, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
