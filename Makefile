# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rpet <marvin@codam.nl>                       +#+                      #
#                                                    +#+                       #
#    Created: 2020/01/23 13:50:37 by rpet          #+#    #+#                  #
#    Updated: 2020/01/30 10:11:41 by rpet          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = gcc
SRCS = main.c
OBJS = $(SRCS:.c=.o)
MLXDYL = libmlx.dylib
MLXDIR = mlx/
HEADER = cub3d.h
FLAGS = -Wall -Werror -Wextra

all: $(NAME)

%.o: %.c $(HEADER)
		$(CC) $(FLAGS) -Imlx -c $< -o $@

$(MLXDYL):
		cd $(MLXDIR) && make && mv $(MLXDYL) ..

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
