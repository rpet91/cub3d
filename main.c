/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/24 09:46:50 by rpet          #+#    #+#                 */
/*   Updated: 2020/02/17 11:49:45 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "cub3d.h"
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

# define MAX_X 800
# define MAX_Y 800

#define tex_width 64
#define tex_height 64
#define map_width 24
#define map_height 24

int worldmap[map_width][map_height]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int		move_player(t_data *mlx)
{
	int		sign;

	mlx->move.move_speed = 0.08; //nog niet juist
	mlx->move.rot_speed = 0.05; //nog niet juist
	if (mlx->move.w == 1 || mlx->move.s == 1)
	{
		sign = (mlx->move.w == 1) ? 1 : -1;
		sign *= (mlx->move.w == mlx->move.s) ? 0 : 1;
		if (!worldmap[(int)mlx->pos.pos_y][(int)(mlx->pos.pos_x +
					mlx->pos.dir_x * mlx->move.move_speed * sign)])
			mlx->pos.pos_x += (mlx->pos.dir_x * mlx->move.move_speed * sign);
		if (!worldmap[(int)(mlx->pos.pos_y + mlx->pos.dir_y *
					mlx->move.move_speed * sign)][(int)mlx->pos.pos_x])
			mlx->pos.pos_y += (mlx->pos.dir_y * mlx->move.move_speed * sign);
	}
	if (mlx->move.right == 1 || mlx->move.left == 1)
	{
		mlx->move.rot_speed *= (mlx->move.right == 1) ? 1 : -1;
		mlx->move.rot_speed *= (mlx->move.right == mlx->move.left) ? 0 : 1;
		mlx->pos.old_dir_x = mlx->pos.dir_x;
		mlx->pos.dir_x = mlx->pos.dir_x * cos(mlx->move.rot_speed) -
			mlx->pos.dir_y * sin(mlx->move.rot_speed);
		mlx->pos.dir_y = mlx->pos.old_dir_x * sin(mlx->move.rot_speed) +
			mlx->pos.dir_y * cos(mlx->move.rot_speed);
		mlx->pos.old_plane_x = mlx->pos.plane_x;
		mlx->pos.plane_x = mlx->pos.plane_x * cos(mlx->move.rot_speed) -
			mlx->pos.plane_y * sin(mlx->move.rot_speed);
		mlx->pos.plane_y = mlx->pos.old_plane_x * sin(mlx->move.rot_speed) +
			mlx->pos.plane_y * cos(mlx->move.rot_speed);
	}
	return (0);
}

int		mlx_setup(t_data *mlx)
{
	mlx->mlx = mlx_init();
	if (mlx->mlx == NULL)
		return (-1);
	mlx->win = mlx_new_window(mlx->mlx, MAX_X, MAX_Y, "Scherm");
	if (mlx->win == NULL)
		return (-1);
	mlx->img1.img = mlx_new_image(mlx->mlx, MAX_X, MAX_Y);
	mlx->img2.img = mlx_new_image(mlx->mlx, MAX_X, MAX_Y);
	if (mlx->img1.img == NULL || mlx->img2.img == NULL)
		return (-1);
	mlx->img1.addr = mlx_get_data_addr(mlx->img1.img,
		&mlx->img1.bits_per_pixel, &mlx->img1.line_length, &mlx->img1.endian);
	mlx->img2.addr = mlx_get_data_addr(mlx->img2.img,
		&mlx->img2.bits_per_pixel, &mlx->img2.line_length, &mlx->img2.endian);
	mlx->active_img = 1;
	mlx->pos.pos_x = 22;
	mlx->pos.pos_y = 12;
	mlx->pos.dir_x = -1;
	mlx->pos.dir_y = 0;
	mlx->pos.plane_x = 0;
	mlx->pos.plane_y = -0.66;
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
		error_handling("Invalid map.");
	error = mlx_setup(&mlx);
	if (error == -1)
		error_handling("Something went wrong during the setup.");
	mlx.map = map;
	mlx_hook(mlx.win, 2, 0, key_press, &mlx);
	mlx_hook(mlx.win, 3, 1L<<1, key_release, &mlx);
	mlx_hook(mlx.win, 17, 1L<<17, close_window, &mlx);
	mlx_do_key_autorepeatoff(mlx.mlx);
	mlx_loop_hook(mlx.mlx, frame_loop, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
