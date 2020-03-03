# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rpet <marvin@codam.nl>                       +#+                      #
#                                                    +#+                       #
#    Created: 2020/01/23 13:50:37 by rpet          #+#    #+#                  #
#    Updated: 2020/03/03 09:27:45 by rpet          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = gcc
_SRCS = main.c render_frame.c hook_functions.c draw_functions.c move_player.c \
	   error_and_free_functions.c raycasting.c empty_struct.c \
	   texture_functions.c sprite_setup.c sprite_sorting.c \
	   parse_map1.c parse_map2.c parse_map3.c map_validation.c \
	   ft_putstr_fd.c ft_strlen.c ft_strchr.c ft_strjoin.c ft_strdup.c \
	   ft_strcpy.c ft_split.c ft_atoi.c ft_strncmp.c ft_memcpy.c ft_memset.c
_OBJS := $(_SRCS:.c=.o)
SRCSDIR = srcs/
OBJSDIR = objs/
SRCS = $(addprefix $(SRCSDIR),$(_SRCS))
OBJS = $(addprefix $(OBJSDIR),$(_OBJS))
MLXDYL = libmlx.dylib
MLXDIR = mlx/
FRAMEWORK = -framework OpenGL -framework AppKit
HEADER = cub3d.h
FLAGS = -Wall -Werror -Wextra

.PHONY: all clean fclean re bonus

all: $(NAME)

$(OBJSDIR)%.o: $(SRCSDIR)%.c $(HEADER)
		$(CC) $(FLAGS) -Imlx -c $< -o $@

$(MLXDYL):
		cd $(MLXDIR) && make && cp $(MLXDYL) ..

$(NAME): $(MLXDYL) $(OBJS)
		$(CC) -L. -lmlx $(FRAMEWORK) -o $(NAME) $(OBJS)
clean:
		rm -f $(OBJS)
		cd $(MLXDIR) && make clean
		rm -f $(MLXDYL)

fclean: clean
		rm -f $(NAME)

re: fclean all

bonus: $(NAME)
