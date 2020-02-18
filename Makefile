# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rpet <marvin@codam.nl>                       +#+                      #
#                                                    +#+                       #
#    Created: 2020/01/23 13:50:37 by rpet          #+#    #+#                  #
#    Updated: 2020/02/18 11:15:31 by rpet          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = gcc
SRCS = main.c render_frame.c hook_functions.c draw_functions.c error_handling.c \
	   parse_map1.c parse_map2.c parse_map3.c map_validation.c free_array.c 
UTILSSRCS = ft_putstr_fd.c ft_strlen.c ft_strchr.c ft_strjoin.c ft_strdup.c \
			ft_strcpy.c ft_split.c ft_atoi.c ft_strncmp.c
OBJS = $(SRCS:.c=.o)
UTILSDIR = utils/
UTILSOBJS = $(addprefix $(UTILSDIR),$(UTILSSRCS:.c=.o))
MLXDYL = libmlx.dylib
MLXDIR = mlx/
FRAMEWORK = -framework OpenGL -framework AppKit
HEADER = cub3d.h
FLAGS = -Wall -Werror -Wextra

.PHONY: all clean fclean re bonus

all: $(NAME)

%.o: %.c $(HEADER)
		$(CC) $(FLAGS) -Imlx -c $< -o $@

$(MLXDYL):
		cd $(MLXDIR) && make && cp $(MLXDYL) ..

$(NAME): $(MLXDYL) $(OBJS) $(UTILSOBJS)
		$(CC) -L. -lmlx $(FRAMEWORK) -o $(NAME) $(OBJS) $(UTILSOBJS)

clean:
		rm -f $(OBJS) $(UTILSOBJS)
		cd $(MLXDIR) && make clean
		rm -f $(MLXDYL)

fclean: clean
		rm -f $(NAME)

re: fclean all

bonus: $(NAME)


