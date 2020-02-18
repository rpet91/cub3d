/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/29 14:18:01 by rpet          #+#    #+#                 */
/*   Updated: 2020/02/18 14:08:02 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> //norm

#ifndef CUB3D_H
# define CUB3D_H

# define MAX_RESOLUTION_X 2560
# define MAX_RESOLUTION_Y 1440
# define BUFF_SIZE 128
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

typedef struct	s_vector	{
	int			x;
	int			y;
}				t_vector;

typedef struct	s_map	{
	t_vector	player_coords;
	t_vector	resolution;
	char		*north_tex;
	char		*south_tex;
	char		*west_tex;
	char		*east_tex;
	char		*sprite_tex;
	int			floor_rgb;
	int			ceiling_rgb;
	int			check;
	char		**map;
}				t_map;

typedef struct	s_data	{
	void		*mlx;
	void		*win;
	t_image		img1;
	t_image		img2;
	t_move		move;
	t_pos		pos;
	t_ray		ray;
	t_map		map;
	int			active_img;
	int			color;
}				t_data;

int				frame_loop(t_data *mlx);
int				worldmap[map_width][map_height];
int				move_player(t_data *mlx);
int				mlx_setup(t_data *mlx);

/*
**		Draw functions
*/

void			put_pixel(t_image *img, int x, int y, int color);
int				draw_image(t_data *mlx, int x);

/*
**		Hook functions
*/

int				key_press(int keycode, t_data *mlx);
int				key_release(int keycode, t_data *mlx);
int				close_window(t_data *mlx);

/*
**		Map functions
*/

int				check_valid_info(t_map *map, char *line);
char			*cut_line(char *line);
int				process_cub_info(t_map *map, char *str, char *line);
int				read_cub_file(t_map *map, int fd);
int				parse_map(t_map *map, char *str);

int				end_of_line(t_map *map);
int				map_resolution(t_map *map, char *line);
int				get_color(char *color_line);
int				map_read_color(int *rgb, char *line, char *loc, int check);
int				map_read_texture(char **wall, char *line, char *loc, int check);

void			create_empty_map(t_map *map);
char			**add_line_to_map(char **old_map, char *new_line);
char			*remove_spaces(char *str);
int				map_information(t_map *map, char *line);

char			**copy_original_map(t_map *map);
int				flood_fill(t_map *map);
int				check_valid_map(t_map *map);

/*
**		Error handler
*/

void			error_handling(char *str);

/*
**		Free functions
*/

void			free_array(char **str);

/*
**		Util functions
*/

void			ft_putstr_fd(char *str, int fd);
int				ft_strlen(char *str);
int				ft_strchr(char *str, char c);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_strdup(char *str);
void			ft_strcpy(char *dst, char *src);
char			**ft_split(char const *s, char c);
int				ft_atoi(const char *str);
int				ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
