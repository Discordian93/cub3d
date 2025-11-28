# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::   #
#    Makefile                                           :+:      :+:    :+:   #
#                                                     +:+ +:+         +:+     #
#    By: student <student@42.fr>                    +#+  +:+       +#+        #
#                                                 +#+#+#+#+#+   +#+           #
#    Created: 2024/01/01 00:00:00 by student           #+#    #+#             #
#    Updated: 2024/01/01 00:00:00 by student          ###   ########.fr       #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I./includes -I./libft -I./mlx

LIBFT = libft/libft.a
MLX = mlx/libmlx.a
LIBS = $(LIBFT) $(MLX) -lX11 -lXext -lm

SRC_DIR = src
PARSE_DIR = src/parsing

SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/init.c \
       $(SRC_DIR)/init_textures.c \
       $(SRC_DIR)/utils.c \
       $(SRC_DIR)/cleanup.c \
       $(SRC_DIR)/raycasting.c \
       $(SRC_DIR)/render.c \
       $(SRC_DIR)/render_wall.c \
       $(SRC_DIR)/hooks.c \
       $(SRC_DIR)/movement.c \
       $(SRC_DIR)/movement_rotate.c \
       $(PARSE_DIR)/parsing_main.c \
       $(PARSE_DIR)/parsing_file.c \
       $(PARSE_DIR)/parsing_utils.c \
       $(PARSE_DIR)/parsing_utils2.c \
       $(PARSE_DIR)/parsing_elements.c \
       $(PARSE_DIR)/parsing_textures.c \
       $(PARSE_DIR)/parsing_colors.c \
       $(PARSE_DIR)/parsing_colors2.c \
       $(PARSE_DIR)/parsing_map.c \
       $(PARSE_DIR)/parsing_map2.c \
       $(PARSE_DIR)/validation_map.c \
       $(PARSE_DIR)/validation_walls.c

OBJS = $(SRCS:.c=.o)

all: libs $(NAME)

libs:
	@make -C libft
	@if [ -d "mlx" ] && [ ! -f "mlx/libmlx.a" ]; then \
		cd mlx && ./configure && make -f makefile.gen; \
	fi

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@echo "Built $(NAME)"

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@make -C libft clean
	rm -f $(OBJS)

fclean: clean
	@make -C libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all libs clean fclean re
