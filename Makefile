CC		= cc
NAME	= fdf
CFLAGS	= -Wextra -Wall -Werror -Wunreachable-code -Ofast
LIBMLX	= ./MLX42

HEADERS	= -I ./include -I $(LIBMLX)/include
LIBS	= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
SRCS	= fdf.c
OBJS	= ${SRCS:.c=.o}

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

#make it so that it automatically recreates the library repository each time

all: libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME) $(LIBFT)

$(LIBFT):
	@make -C $(LIBFT_DIR)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build
	@make clean -C $(LIBFT_DIR)

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C $(LIBFT_DIR)

re: clean all

.PHONY: all, clean, fclean, re, libmlx


# linking: see https://github.com/codam-coding-college/MLX42/blob/master/docs/index.md 	-lglfw(3) -framework Cocoa -framework OpenGL -framework IOKit




# CC			= cc
# NAME		= pipex
# SRCS		= pipex.c
# OBJS		= $(SRCS:.c=.o)
# HEAD		= pipex.h
# # NAME_B		= pipex_bonus
# # SRCS_B		= pipex_bonus.c
# # OBJS_B		= $(SRCS_B:.c=.o)
# # HEAD_B		= pipex_bonus.h
# CFLAGS		= -Wall -Werror -Wextra
# PRINTF_DIR	= printf
# PRINTF		= $(PRINTF_DIR)/libftprintf.a
# LIBFT_DIR	= libft
# LIBFT		= $(LIBFT_DIR)/libft.a

# all:	$(NAME)

# $(NAME): $(OBJS) $(HEAD) $(PRINTF) $(LIBFT)
# 	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(PRINTF) $(LIBFT)

# # bonus: $(NAME_B)

# # $(NAME_B): $(OBJS) $(OBJS_B) $(HEAD_B) $(HEAD) $(PRINTF)
# # 	$(CC) $(CFLAGS) -o $(NAME_B) $(OBJS) $(OBJS_B) $(PRINTF)

# $(PRINTF):
# 	@make -C $(PRINTF_DIR)

# $(LIBFT):
# 	@make -C $(LIBFT_DIR)

# clean:
# 	@rm -f $(OBJS)
# 	@rm -f $(OBJS_B)
# 	@make clean -C $(PRINTF_DIR)
# 	@make clean -C $(LIBFT_DIR)

# fclean:	clean
# 	@rm -f $(NAME)
# 	@rm -f $(NAME_B)
# 	@make fclean -C $(PRINTF_DIR)
# 	@make fclean -C $(LIBFT_DIR)

# re:		fclean all

# .PHONY: all clean fclean re bonus