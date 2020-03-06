# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rpet <marvin@codam.nl>                       +#+                      #
#                                                    +#+                       #
#    Created: 2020/01/23 13:50:37 by rpet          #+#    #+#                  #
#    Updated: 2020/03/06 10:03:09 by rpet          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = gcc
_SRCS = main.c render_frame.c hook_functions.c draw_functions.c move_player.c \
	   raycasting.c free_functions.c error_functions.c texture_functions.c \
	   sprite_setup.c sprite_sorting.c parse_map1.c parse_map2.c parse_map3.c \
	   map_validation.c empty_struct_functions.c bmp.c
_OBJS := $(_SRCS:.c=.o)
SRCSDIR = srcs/
OBJSDIR = objs/
SRCS = $(addprefix $(SRCSDIR),$(_SRCS))
OBJS = $(addprefix $(OBJSDIR),$(_OBJS))
MLXDYL = libmlx.dylib
MLXDIR = mlx/
LIBFT = libft.a
LIBFTDIR = libft/
FRAMEWORK = -framework OpenGL -framework AppKit
HEADER = cub3d.h
FLAGS = -Wall -Werror -Wextra

.PHONY: all clean fclean re bonus

all: $(NAME)

$(OBJSDIR)%.o: $(SRCSDIR)%.c $(HEADER)
		mkdir -p objs
		$(CC) $(FLAGS) -Imlx -c $< -o $@

$(MLXDYL):
		cd $(MLXDIR) && make && mv $(MLXDYL) ..

$(LIBFT):
		cd $(LIBFTDIR) && make && mv $(LIBFT) ..

$(NAME): $(MLXDYL) $(LIBFT) $(OBJS)
		$(CC) -L. -lmlx -lft $(FRAMEWORK) -o $(NAME) $(OBJS)

clean:
		rm -f $(OBJS)
		cd $(MLXDIR) && make clean
		cd $(LIBFTDIR) && make clean
		rm -f $(MLXDYL)

fclean: clean
		rm -f $(NAME) $(LIBFT)

re: fclean all

bonus: $(NAME)
