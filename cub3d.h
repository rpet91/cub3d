/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/29 14:18:01 by rpet          #+#    #+#                 */
/*   Updated: 2020/02/05 15:30:25 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> //norm

#ifndef CUB3D_H
# define CUB3D_H

# define COLOR_R 0x00FF0000
# define COLOR_G 0x0000FF00
# define COLOR_B 0x000000FF
# define ESC_BUTTON 53
# define KEY_W 13
# define KEY_S 1
# define KEY_A 0
# define KEY_D 2
# define KEY_LEFT 123
# define KEY_RIGHT 124

# define MAX_X 800
# define MAX_Y 800

#define tex_width 64
#define tex_height 64
#define map_width 24
#define map_height 24

typedef struct	s_ray {
	double		cam_x;
	double		raydir_x;
	double		raydir_y;
	double		sidedist_x;
	double		sidedist_y;
	double		deltadist_x;
	double		deltadist_y;
	double		perpwalldist;
}				t_ray;

typedef struct	s_pos {
	int			map_x;
	int			map_y;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		old_dir_x;
	double		old_plane_x;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
}				t_pos;

typedef struct	s_move {
	int			w;
	int			s;
	int			a;
	int			d;
	int			left;
	int			right;
	int			step_x;
	int			step_y;
	double		move_speed;
	double		rot_speed;
}				t_move;

typedef struct	s_image {
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_image;

typedef struct	s_data	{
	void		*mlx;
	void		*win;
	t_image		img1;
	t_image		img2;
	t_move		move;
	t_pos		pos;
	t_ray		ray;
	int			active_img;
	int			color;
}				t_data;

int		frame_loop(t_data *mlx);
int		worldmap[map_width][map_height];
int		move_player(t_data *mlx);
void	put_pixel(t_image *img, int x, int y, int color);
int		draw_image(t_data *mlx, int x);
int		mlx_setup(t_data *mlx);

/*
**		Hook functions
*/

int		key_press(int keycode, t_data *mlx);
int		key_release(int keycode, t_data *mlx);
int		close_window(t_data *mlx);

#endif
