/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d_bonus.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/29 14:18:01 by rpet          #+#    #+#                 */
/*   Updated: 2020/06/02 07:58:26 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "defines.h"
# include "libft/libft.h"
# include <stdlib.h>

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
**		Struct for the sprite drawing calculations.
*/

typedef struct		s_draw_sprite {
	t_vector_d		sprite;
	t_vector_d		transform;
	t_vector_i		draw_start;
	t_vector_i		draw_end;
	t_vector_i		tex;
	t_vector_i		draw;
	double			inv_det;
	unsigned int	rgb;
	int				size;
	int				screen;
}					t_draw_sprite;

/*
**		Struct for the raycasting calculations.
*/

typedef struct		s_ray {
	int				hit;
	int				side_hit;
	int				line_height;
	int				draw_start;
	int				draw_end;
	double			cam_x;
	double			perpwalldist;
	double			*dis_buffer;
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
**		Struct for the floor textures;
*/

typedef struct		s_floor {
	t_vector_d		ray1;
	t_vector_d		ray2;
	t_vector_d		step;
	t_vector_d		pos;
	t_vector_i		cell;
	t_vector_i		t;
	double			row_dis;
	int				cur_p;
}					t_floor;

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
	t_texture		floor;
	t_texture		ceiling;
}					t_list_tex;

/*
**		Struct information for every individual sprite.
*/

typedef struct		s_sprite {
	t_vector_d		coords;
	t_texture		texture;
	double			dis;
}					t_sprite;

/*
**		Struct for a list of sprites.
*/

typedef struct		s_list_sprite {
	int				amount;
	t_sprite		**sprites;
}					t_list_sprite;

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
	char			*line;
	char			*north_tex;
	char			*south_tex;
	char			*west_tex;
	char			*east_tex;
	char			*sprite_tex;
	char			*floor_tex;
	char			*ceiling_tex;
	int				floor_rgb;
	int				ceiling_rgb;
	int				check;
	int				fd;
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
	t_list_sprite	list;
	t_draw_sprite	draw_sprite;
	t_move			move;
	t_ray			ray;
	t_ray_tex		ray_tex;
	t_map			map;
	t_floor			floor;
	int				active_img;
	int				mouse;
}					t_data;

/*
**		The engine of the game.
*/

int					frame_loop(t_data *mlx);
void				screenshot_frame_loop(t_data *mlx);

/*
**		The main setup of the game.
*/

void				starting_face_direction(t_data *mlx, int y, int x);
void				get_correct_window_resolution(t_data *mlx);
void				mlx_setup(t_data *mlx);

/*
**		BMP functions.
*/

int					draw_screenshot(t_data *mlx, int fd);
unsigned int		bmp_size(int width, int height);
void				bmp_header(t_data *mlx, int x, int y, int fd);
void				calculate_sprite_size_on_screen(t_data *mlx);
void				create_image_data(t_data *mlx);
void				make_screenshot(t_data *mlx);

/*
**		Sprite functions.
*/

void				sort_sprites(t_data *mlx);
void				calculate_distances(t_data *mlx);
void				calculate_sprite_depth(t_data *mlx);
void				sprite_engine(t_data *mlx, t_image *cur_img);

t_sprite			**add_sprite_to_array(t_data *mlx, t_sprite *new_sprite);
t_sprite			*create_new_sprite(t_data *mlx, int y, int x);
void				locate_sprites(t_data *mlx);
void				sprite_setup(t_data *mlx);

/*
**		Texture functions.
*/

t_texture			*get_wall_texture(t_data *mlx);
void				calculate_texture(t_data *mlx);
t_texture			*select_texture_img(t_data *mlx, int i);
void				convert_to_image(t_data *mlx, t_texture *tex);
void				texture_setup(t_data *mlx);

/*
**		Floor drawing functions.
*/

void				floors_raycast(t_data *mlx, int y);
int					floor_rgb(t_data *mlx, int color, t_texture *tex, int y);
void				calculate_ray_size(t_data *mlx);
void				draw_texture_pixel(t_data *mlx, t_image *cur_img, int y);
void				draw_floors(t_data *mlx, t_image *cur_img);

/*
**		Draw functions.
*/

int					add_shades(int rgb, double distance);

unsigned int		get_pixel(t_image *img, int x, int y);
void				put_pixel(t_image *img, int x, int y, int color);
void				draw_solid_floors(t_data *mlx, t_image *cur_img);
void				draw_wall_texture(t_data *mlx, int x, t_image *cur_img);
void				draw_sprites(t_data *mlx, t_sprite *cur,
										t_image *cur_img, t_draw_sprite *spr);

/*
**		Hook functions.
*/

int					key_press(int keycode, t_data *mlx);
int					key_release(int keycode, t_data *mlx);
int					mouse_move(int x, int y, t_data *mlx);
int					close_game(t_data *mlx);

/*
**		Raycasting functions.
*/

void				check_draw_coords(t_data *mlx);
void				calculate_wall_distance(t_data *mlx, int x);
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

void				check_valid_info(t_data *mlx, char *line);
int					process_cub_info(t_data *mlx, char *str);
int					read_cub_file(t_data *mlx, int fd);
void				parse_map(t_data *mlx, char *str);

void				map_resolution(t_data *mlx, char *str);
int					get_color(char *color_line);
void				read_color(char **tex, int *rgb, char *str, t_data *mlx);
void				read_tex(char **tex, char *str, t_data *mlx);

void				element_validation(t_data *mlx);
char				**make_rectangle(t_data *mlx);
char				**add_line_to_map(char **old_map, char *new_line, int y);
char				*find_player_pos(t_data *mlx, char *str);
void				map_information(t_data *mlx, char *line);

int					check_closed(t_data *mlx, char **copy_map, int y, int x);
void				create_copy_map(t_data *mlx, int max_y, int max_x);
void				check_valid_map(t_data *mlx);

/*
**		Empty struct functions.
*/

void				empty_map(t_data *mlx);
void				empty_textures(t_data *mlx);
void				empty_mlx(t_data *mlx);

/*
**		Error and free functions.
*/

void				free_array(char **str);
void				free_sprite_array(t_data *mlx);
void				destroy_textures(t_data *mlx);
void				free_map(t_data *mlx);
void				destroy_mlx(t_data *mlx);

void				error_message(char *str);
void				error_handling(char *str, t_data *mlx);

#endif
