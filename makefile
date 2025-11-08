# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yuliano <yuliano@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/11 05:32:19 by yuliano           #+#    #+#              #
#    Updated: 2025/11/08 22:04:19 by yuliano          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
OBJ_DIR = ./obj
SRC_DIR = ./src
CFLAGS =  -g -I./libft -I./ -I./mlx 
LIBS = libft/libft.a ./mlx/libmlx.a -lX11 -lXext -lm

OBJS = $(OBJ_DIR)/util1.o \
	$(OBJ_DIR)/util2.o \
	$(OBJ_DIR)/main.o \
	$(OBJ_DIR)/map_read.o \
	$(OBJ_DIR)/raycasting.o
all: libs $(NAME)
	
# Compila o recompila la libft
libs:
	@make -C libft
	@make -C mlx

# Compila el programa principal
$(NAME): $(OBJS)
	gcc $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@echo "✅ DONE"

# Compila los archivos .c a .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	gcc -c $(CFLAGS) $< -o $@

# Limpieza de archivos objeto
clean:
	@make clean -C libft
	@make clean -C mlx
	rm -fr $(OBJ_DIR)

fclean: clean
	@make fclean -C libft
	@make clean -C mlx
	rm -f mlx/libmlx.a
	rm -f $(NAME)
	@echo "✅ CLEAN DONE"


# Reconstrucción completa
re: fclean all

.PHONY: all clean fclean