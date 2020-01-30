/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/29 14:18:01 by rpet          #+#    #+#                 */
/*   Updated: 2020/01/30 18:06:45 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define ESC_BUTTON 53
# define KEY_W 13
# define KEY_S 1
# define KEY_A 0
# define KEY_D 2

int		main(void);

typedef struct	s_move {
	int			w;
	int			s;
	int			a;
	int			d;
}				t_move;

typedef struct	s_image {
	void		*img;
	void		*img_new;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_image;

typedef struct	s_data	{
	void		*mlx;
	void		*mlx_win;
	t_image		*img;
	t_move		*move;
	int			x;
	int			y;
}				t_data;

#endif
