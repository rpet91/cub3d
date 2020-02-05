# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rpet <marvin@codam.nl>                       +#+                      #
#                                                    +#+                       #
#    Created: 2020/01/23 13:50:37 by rpet          #+#    #+#                  #
#    Updated: 2020/02/05 15:26:36 by rpet          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC = gcc
SRCS = main.c render_frame.c hook_functions.c
OBJS = $(SRCS:.c=.o)
MLXDYL = libmlx.dylib
MLXDIR = mlx/
HEADER = cub3d.h
FLAGS = -Wall -Werror -Wextra

all: $(NAME)

%.o: %.c $(HEADER)
		$(CC) $(FLAGS) -Imlx -c $< -o $@

$(MLXDYL):
		cd $(MLXDIR) && make && cp $(MLXDYL) ..

$(NAME): $(MLXDYL) $(OBJS)
		$(CC) -L. -lmlx -framework OpenGL -framework AppKit -o $(NAME) $(OBJS)


clean:
		rm -f $(OBJS)
		cd $(MLXDIR) && make clean
		rm -f $(MLXDYL)

fclean: clean
		rm -f $(NAME)

re: fclean all

bonus: $(NAME)


