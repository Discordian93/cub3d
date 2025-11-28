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

NAME = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCS = ft_strlen.c \
       ft_strdup.c \
       ft_strncmp.c \
       ft_strchr.c \
       ft_strlcpy.c \
       ft_atoi.c \
       ft_bzero.c \
       ft_calloc.c \
       ft_putstr_fd.c \
       ft_putchar_fd.c \
       ft_split.c \
       get_next_line.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c libft.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
