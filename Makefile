NAME = cub3D

CC = cc -std=gnu11
CFLAGS = -Wall -Wextra -Werror -g -Iinclude -I$(MLX_DIR)
LDFLAGS = -L$(MLX_DIR)

UNAME = $(shell uname -s)
ifeq ($(UNAME), Linux)
	MLX_DIR = lib/minilibx
	CFLAGS += -D_LINUX_
	LDFLAGS += -lmlx -lXext -lX11 -lm
else
	MLX_DIR = lib/minilibx-macos
	LDFLAGS += -lmlx -lm -framework OpenGL -framework AppKit
endif

# Shared
SRC = src/main.c src/image.c src/time.c src/mlx_hook.c src/cub3d_frame.c src/cub3d_math.c
SRC += src/utils.c src/utils2.c src/utils3.c src/image2.c src/cub3d_frame_mvt.c
# Parsing
SRC += parsing/parsing.c parsing/parse_map_content.c parsing/parse_map_config.c
SRC += parsing/get_next_line.c parsing/map_validate.c
# Raycasting
SRC += raycasting/raycasting.c raycasting/raycasting_render.c
OBJ = $(SRC:.c=.o)

all: lib $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(NAME) $(LDFLAGS)

lib:
	make CC=clang -C $(MLX_DIR)
	
libclean:
	make clean -C $(MLX_DIR)

clean:
	rm -f $(OBJ)

fclean: libclean clean
	rm -f $(NAME)

re: fclean all

.PHONY: all lib libclean clean fclean re
