NAME    = cub3D
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -Iincludes

libft_PATH = ./libft
libft_LIB  = $(libft_PATH)/libft.a
MLX_PATH = ./minilibx-linux
MLX_LIB  = $(MLX_PATH)/libmlx.a
MLX_FLAGS = -L$(MLX_PATH) -lmlx -L/usr/lib -lXext -lX11 -lm -lz

SRC     = src/main.c \
		  src/get_next_line.c \
		  src/ft_pasing.c \

OBJ     = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(MLX_PATH)
	@make -C $(libft_PATH)
	$(CC) $(OBJ)  $(libft_LIB) $(MLX_LIB) $(MLX_FLAGS) -o $(NAME)

clean:
	@make -C $(MLX_PATH) clean
	@make -C $(libft_PATH) clean
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re