/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/29 14:18:01 by rpet          #+#    #+#                 */
/*   Updated: 2020/02/26 09:27:19 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> //norm

#ifndef CUB3D_H
# define CUB3D_H

# define BUFF_SIZE 128
# define ESC_BUTTON 53
# define KEY_W 13
# define KEY_S 1
# define KEY_A 0
# define KEY_D 2
# define KEY_LEFT 123
# define KEY_RIGHT 124

# define MALLOC "Something went wrong with allocating memory."
# define MLX_ERROR "Something went wrong with the mlx setup."
# define TEXTURE_ERROR "Something went wrong with the texture setup."
# define NO_CUB "No valid map file given. A .cub file is needed."
# define READ_ERROR "Something went wrong while reading the file."
# define OPEN_MAP "Invalid map. Map is not surrounded by walls."
# define INVALID_CHAR "Found an invalid character in the cub file."
# define NO_INFO "Didn't receive enough map info."
# define WRONG_INFO "Received wrong info in one or more elements."
# define WRONG_COLOR "Invalid color information."
# define WRONG_TEXTURE "Invalid texture location/file."
# define WRONG_RES_SIZE "Given resolution is too small."
# define WRONG_PLAYER_POS "Received zero or more than one starting coords."

/*
**		Two structs for vector values.
*/

typedef struct		s_vector_d {
	double			x;
	double			y;
}					t_vector_d;

typedef struct		s_vector_i {
	int				x;
	int				y;
}					t_vector_i;

/*
**		Struct needed for the raycasting calculations.
*/

typedef struct		s_ray {
	int				hit;
	int				side_hit;
	int				line_height;
	int				draw_start;
	int				draw_end;
	double			cam_x;
	double			perpwalldist;
	t_vector_i		map;
	t_vector_i		step;
	t_vector_d		ray;
	t_vector_d		side;
	t_vector_d		delta;
	t_vector_d		dir;
	t_vector_d		plane;
}					t_ray;

/*
**		Struct for the player movement.
*/

typedef struct		s_move {
	int				w;
	int				s;
	int				a;
	int				d;
	int				left;
	int				right;
	double			move_speed;
	double			rot_speed;
	t_vector_d		pos;
}					t_move;

/*
**		Struct when a new image is created.
*/

typedef struct		s_image {
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_image;

/*
**		Struct for information about a texture.
*/

typedef struct		s_texture {
	t_image			img;
	char			*path;
	int				w;
	int				h;
}					t_texture;


/*
**		Struct for a list of texture structs.
*/

typedef struct		s_list_tex {
	t_texture		north;
	t_texture		south;
	t_texture		west;
	t_texture		east;
	t_texture		sprite;
}					t_list_tex;

/*
**		Struct for texture raycasting calculations.
*/

typedef struct		s_ray_tex {
	double			step;
	double			tex_pos;
	double			wall_x;
	t_vector_i		tex;
}					t_ray_tex;

/*
**		Struct for reading out a .cub file.
*/

typedef struct		s_map {
	t_vector_i		player;
	t_vector_i		res;
	t_vector_i		size;
	char			*north_tex;
	char			*south_tex;
	char			*west_tex;
	char			*east_tex;
	char			*sprite_tex;
	int				floor_rgb;
	int				ceiling_rgb;
	int				check;
	char			**map;
}					t_map;

/*
**		The main struct.
*/

typedef struct		s_data {
	void			*mlx;
	void			*win;
	t_image			img1;
	t_image			img2;
	t_list_tex		list_tex;
	t_move			move;
	t_ray			ray;
	t_ray_tex		ray_tex;
	t_map			map;
	int				active_img;
	int				color;
}					t_data;

/*
**		The engine of the game.
*/

int					frame_loop(t_data *mlx);

/*
**		The main setup of the game.
*/

void				starting_face_direction(t_data *mlx, int y, int x);
void				get_correct_window_resolution(t_data *mlx);
int					mlx_setup(t_data *mlx);

/*
**		Texture functions.
*/

t_texture			*get_texture_path(t_data *mlx);
void				calculate_texture(t_data *mlx);
t_texture			*select_texture_img(t_data *mlx, int i);
int					texture_setup(t_data *mlx);

/*
**		Draw functions.
*/

unsigned int		get_pixel(t_image *img, int x, int y);
void				put_pixel(t_image *img, int x, int y, int color);
void				draw_texture(t_data *mlx, int x, int y, t_image *cur_img);
void				draw_image(t_data *mlx, int x, t_image *cur_img);

/*
**		Hook functions.
*/

int					key_press(int keycode, t_data *mlx);
int					key_release(int keycode, t_data *mlx);
int					close_window(t_data *mlx);

/*
**		Struct functions.
*/

void				create_empty_map(t_map *map);

/*
**		Raycasting functions.
*/

void				check_draw(t_data *mlx);
void				check_wall_hit(t_data *mlx);
void				check_player_direction(t_data *mlx);
void				calculate_variables(t_data *mlx, int x);

/*
**		Move functions.
*/

void				move_forward_or_backward(t_data *mlx, double dir);
void				strafe_player(t_data *mlx, double dir);
void				rotate_player(t_data *mlx, double dir);
void				move_player(t_data *mlx);

/*
**		Map parsing functions.
*/

int					check_valid_info(t_map *map, char *line);
char				*cut_line(char *line);
int					process_cub_info(t_map *map, char *str, char *line);
int					read_cub_file(t_map *map, int fd);
int					parse_map(t_map *map, char *str);

int					end_of_line(t_map *map);
int					map_resolution(t_map *map, char *line);
int					get_color(char *color_line);
int					map_read_color(int *rgb, char *line, char *loc, int check);
int					map_read_tex(char **wall, char *line, char *loc, int check);

char				**make_rectangle(t_map *map);
char				**add_line_to_map(char **old_map, char *new_line, int y);
char				*remove_spaces(t_map *map, char *str);
int					map_information(t_map *map, char *line);

int					check_closed_map(t_map *map, char **copy_map, int y, int x);
int					create_copy_map(t_map *map, int max_y, int max_x);
int					check_valid_map(t_map *map);

/*
**		Error and free functions.
*/

int					error_handling(char *str);
void				free_array(char **str);

/*
**		Util functions.
*/

void				ft_putstr_fd(char *str, int fd);
int					ft_strlen(char *str);
int					ft_strchr(char *str, char c);
char				*ft_strjoin(char *s1, char *s2);
char				*ft_strdup(char *str);
void				ft_strcpy(char *dst, char *src);
char				**ft_split(char const *s, char c);
int					ft_atoi(const char *str);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memset(void *b, int c, size_t len);

#endif
