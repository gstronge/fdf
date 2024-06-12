# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/08 13:34:20 by gstronge          #+#    #+#              #
#    Updated: 2024/06/12 20:13:46 by gstronge         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= cc
NAME	= libft.a
SRCS	= ft_isprint.c ft_memcpy.c ft_strchr.c ft_strncmp.c ft_atoi.c \
ft_itoa.c ft_memmove.c ft_strdup.c ft_strnstr.c ft_bzero.c ft_memset.c \
ft_striteri.c ft_strrchr.c ft_calloc.c ft_putchar_fd.c ft_strjoin.c \
ft_strtrim.c ft_isalnum.c ft_putendl_fd.c ft_strlcat.c ft_substr.c \
ft_isalpha.c ft_putnbr_fd.c ft_strlcpy.c ft_tolower.c ft_isascii.c \
ft_memchr.c ft_putstr_fd.c ft_strlen.c ft_toupper.c ft_isdigit.c ft_memcmp.c \
ft_split.c ft_strmapi.c get_next_line.c get_next_line_utils.c
OBJS	= $(SRCS:.c=.o)
SRCSB	= ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
ft_lstclear_bonus.c ft_lstiter_bonus.c
OBJSB	= $(SRCSB:.c=.o)
HEAD	= libft.h get_next_line.h
CFLAGS	= -Wall -Werror -Wextra

all:		$(NAME)

$(NAME):	$(OBJS) $(HEAD)
	ar rsc $(NAME) $(OBJS)

clean:
	rm -f $(OBJS) $(OBJSB)

fclean:		clean
	rm	-f $(NAME)

re:			fclean all

bonus:		all $(OBJSB)
	ar rsc $(NAME) $(OBJSB)

.PHONY:	all clean fclean re bonus