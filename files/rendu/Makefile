NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -I./includes -I./libft -I./minilibx-linux

MLX_PATH = ./minilibx-linux
MLX_LIB = -L$(MLX_PATH) -lmlx -lXext -lX11
MATH_LIB = -lm

LIBFT_PATH = ./libft
LIBFT_LIB = -L$(LIBFT_PATH) -lft

LIBS = $(LIBFT_LIB) $(MLX_LIB) $(MATH_LIB)

SRC_DIR = src
SRC_PARSING = $(SRC_DIR)/parsing/parse_file.c \
			  $(SRC_DIR)/parsing/parse_textures.c \
			  $(SRC_DIR)/parsing/load_textures.c \
			  $(SRC_DIR)/parsing/parse_map.c \
			  $(SRC_DIR)/parsing/validate_map.c \
			  $(SRC_DIR)/parsing/free_map.c
SRC_RAYCAST = $(SRC_DIR)/raycasting/raycast.c \
			  $(SRC_DIR)/raycasting/texture.c
SRC_PLAYER = $(SRC_DIR)/player/move.c \
			 $(SRC_DIR)/player/rotate.c \
			 $(SRC_DIR)/player/collision.c
SRC_RENDER = $(SRC_DIR)/render/draw.c \
			 $(SRC_DIR)/render/hooks.c \
			 $(SRC_DIR)/render/game_loop.c
SRC_UTILS = $(SRC_DIR)/utils/errors.c \
			$(SRC_DIR)/utils/pixel.c \
			$(SRC_DIR)/utils/colors.c \
			$(SRC_DIR)/utils/split_utils.c \
			$(SRC_DIR)/utils/free_game.c
SRC_MAIN = main.c

SRCS = $(SRC_MAIN) $(SRC_PARSING) $(SRC_RAYCAST) $(SRC_PLAYER) $(SRC_RENDER) $(SRC_UTILS)
OBJS = $(SRCS:.c=.o)

all: libft libmlx $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

libft:
	$(MAKE) -C $(LIBFT_PATH)

libmlx:
	$(MAKE) -C $(MLX_PATH)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_PATH) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re libft libmlx
