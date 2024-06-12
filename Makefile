# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/12 19:12:32 by gstronge          #+#    #+#              #
#    Updated: 2024/06/12 20:12:06 by gstronge         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= cc
NAME	= fdf
CFLAGS	= -Wextra -Wall -Werror -Wunreachable-code -Ofast
LIBMLX	= ./MLX42

HEADERS	= -I ./include -I $(LIBMLX)/include
LIBS	= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
SRCS	= make_image.c make_points.c error_cleanup.c set_colours.c fdf.c \
line_calcs.c make_grid.c
OBJS	= ${SRCS:.c=.o}

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

all: libmlx $(NAME)

libmlx: $(LIBMLX)
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME) $(LIBFT)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(LIBMLX):
	@touch .gitmodules
	@git submodule add -f https://github.com/codam-coding-college/MLX42.git

clean:
	rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build
	@make clean -C $(LIBFT_DIR)

fclean: clean
	rm -rf $(NAME)
	@make fclean -C $(LIBFT_DIR)

re: clean all

.PHONY: all, clean, fclean, re, libmlx