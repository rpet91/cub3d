/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   defines.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/10 13:53:35 by rpet          #+#    #+#                 */
/*   Updated: 2020/03/10 13:54:42 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define BUFF_SIZE 128
# define ESC_BUTTON 53
# define KEY_W 13
# define KEY_S 1
# define KEY_A 0
# define KEY_D 2
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define ARGUMENTS "Wrong amount of input arguments."
# define BMP "Second argument needs to be '--save'."
# define MALLOC "Something went wrong with allocating memory."
# define MLX_ERROR "Something went wrong with the mlx setup."
# define TEXTURE_ERROR "Something went wrong with the texture setup."
# define NO_CUB "No valid map file given. A .cub file is needed."
# define INVALID_CUB "The given .cub file can't be opened."
# define READ_ERROR "Something went wrong while reading the file."
# define WRITE_ERROR "Something went wrong while writing the file."
# define OPEN_MAP "Invalid map. Map is not surrounded by walls."
# define INVALID_CHAR "Found an invalid character in the cub file."
# define NO_INFO "Didn't receive enough map info."
# define WRONG_INFO "Received wrong info in one or more elements."
# define WRONG_COLOR "Invalid color information."
# define WRONG_TEXTURE "Invalid texture location/file."
# define WRONG_RES_SIZE "Given resolution is too small."
# define WRONG_RES_CHAR "Invalid characters in the resolution."
# define WRONG_PLAYER_POS "Received zero or more than one starting coords."
# define SCREENSHOT "Failed to create a screenshot.bmp file."

#endif
