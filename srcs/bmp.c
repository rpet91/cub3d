/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bmp.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/04 08:59:52 by rpet          #+#    #+#                 */
/*   Updated: 2020/03/05 16:08:00 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <mlx.h>
#include "../cub3d.h"

int				draw_screenshot(t_data *mlx, int fd)
{
	unsigned int	rgb;
	int				padding;
	int				x;
	int				y;

	y = 0;
	padding = (4 - (mlx->map.res.x * 3) % 4) % 4;
	y = mlx->map.res.y - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < mlx->map.res.x)
		{
			rgb = get_pixel(&mlx->img1, x, y);
			if (write(fd, &rgb, 3) == -1)
				return (-1);
			x++;
		}
		if (write(fd, "\0\0\0", padding) == -1 && padding > 0)
			return (-1);
		y--;
	}
	return (0);
}

/*
**		Creates the header of the screenshot.
*/

void			bmp_header(t_data *mlx, int x, int y, int fd)
{
	unsigned char	*bmp;

	bmp = malloc(sizeof(unsigned char) * 54);
	if (bmp == NULL)
	{
		close(fd);
		error_handling(MALLOC, mlx);
	}
	ft_bzero(bmp, 54);
	*bmp = 0x42;
	*(bmp + 1) = 0x4D;
	*(unsigned int *)(bmp + 2) = (x * 3 + (4 - (x * 3 % 4)) % 4) * y + 54;
	*(unsigned int *)(bmp + 10) = 54;
	*(unsigned int *)(bmp + 14) = 40;
	*(int *)(bmp + 18) = x;
	*(int *)(bmp + 22) = y;
	*(unsigned short *)(bmp + 26) = 1;
	*(unsigned short *)(bmp + 28) = 24;
	if (write(fd, bmp, 54) == -1)
	{
		free(bmp);
		close(fd);
		error_handling(WRITE_ERROR, mlx);
	}
	free(bmp);
}

void			create_image_data(t_data *mlx)
{
	empty_mlx(mlx);
	mlx->mlx = mlx_init();
	if (mlx->mlx == NULL)
		error_handling(MALLOC, mlx);
	mlx->img1.img = mlx_new_image(mlx->mlx, mlx->map.res.x, mlx->map.res.y);
	if (mlx->img1.img == NULL)
		error_handling(MALLOC, mlx);
	mlx->img1.addr = mlx_get_data_addr(mlx->img1.img,
		&mlx->img1.bits_per_pixel, &mlx->img1.line_length, &mlx->img1.endian);
	starting_face_direction(mlx, mlx->map.player.y, mlx->map.player.x);
	mlx->ray.dis_buffer = malloc(sizeof(double) * (mlx->map.res.x));
	if (mlx->ray.dis_buffer == NULL)
		error_handling(MALLOC, mlx);
}

void			make_screenshot(t_data *mlx)
{
	int		fd;

	create_image_data(mlx);
	texture_setup(mlx);
	sprite_setup(mlx);
	screenshot_frame_loop(mlx);
	fd = open("screenshot.bmp", O_RDWR | O_CREAT | O_TRUNC, 0755);
	if (fd == -1)
		error_handling(SCREENSHOT, mlx);
	bmp_header(mlx, mlx->map.res.x, mlx->map.res.y, fd);
	if (draw_screenshot(mlx, fd) == -1)
	{
		close(fd);
		error_handling(WRITE_ERROR, mlx);
	}
	close(fd);
	close_game(mlx);
	exit(0);
}
