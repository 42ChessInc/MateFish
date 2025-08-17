NAME= autoMate

CC = cc

MLX_DIR= ./libs/mlx



$(MLX):
	if [ ! -d "$(MLX_DIR)" ]; then \
			git clone https://github.com/42Paris/minilibx-linux.git $(MLX_DIR); \
	fi
		@$(MAKE) -C $(MLX_DIR)


MLX= $(MLX_DIR)/libmlx.a

CFLAGS = -Wall -Werror -Wextra -Iincludes

LDFLAGS = -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm



SRCS_DIR = ./srcs/main.c \
	./srcs/check_moves.c \
	./srcs/interface/delta.c \
	./srcs/interface/free_displays.c \
	./srcs/interface/ft_pixelput.c \
	./srcs/interface/game_loop.c \
	./srcs/interface/get_time.c \
	./srcs/interface/init_window.c \
	./srcs/interface/interface.c \
	./srcs/interface/load_images.c \
	./srcs/interface/render_utils.c

OBJS_DIR = objs

INC_DIR = includes

$(NAME): $(SRCS_DIR) $(MLX)
	$(CC) $(CFLAGS) $(SRCS_DIR) -o $(NAME) $(LDFLAGS)

fclean: clean
	rm -rf $(NAME)
	rm -rf $(MLX_DIR)
clean:
	rm -rf $(OBJS_DIR)

