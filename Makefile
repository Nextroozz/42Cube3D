NAME = cub3d

CC = cc -std=gnu11
CFLAGS = -Wall -Wextra -Werror -Iinclude -I$(MLX_DIR)
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

SRC = src/main.c src/image.c
SRC += parsing/parsing.c
SRC += raycasting/raycasting.c
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
