NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT = libft/libft.a
MINILIBX = minilibx-linux/libmlx.a
MLXFLAG = -lXext -lX11 -lm

SRC = main.c \
	free.c \
	game_controller.c \
	gfx.c \
	init_value.c \
	map_controller.c \
	map_process.c \
	map_validation.c \
	utils.c \
	utils2.c \
	get_next_line/get_next_line.c \
	get_next_line/get_next_line_utils.c 

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MINILIBX)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFT) $(MINILIBX) $(MLXFLAG)

$(LIBFT):
	make -C libft

$(MINILIBX):
	make -C minilibx-linux

clean:
	rm -f $(OBJ)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re