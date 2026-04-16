# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gde-la-r <gde-la-r@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/20 21:47:37 by gde-la-r          #+#    #+#              #
#    Updated: 2026/04/16 14:14:13 by gde-la-r         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = MateFish
CC          = cc
CFLAGS      = -Wall -Werror -Wextra -Iincludes
LDFLAGS     = -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm

MLX_DIR     = ./libs/mlx
MLX         = $(MLX_DIR)/libmlx.a
STOCK_DIR   = ./Stockfish
STOCK_BIN   = ./stockfish

SRCS_DIR    = ./srcs/main.c \
              ./srcs/check_moves.c \
              ./srcs/interface/delta.c \
              ./srcs/interface/free_displays.c \
              ./srcs/interface/ft_pixelput.c \
              ./srcs/interface/game_loop.c \
              ./srcs/interface/get_time.c \
              ./srcs/interface/init_window.c \
              ./srcs/interface/interface.c \
              ./srcs/interface/load_images.c \
              ./srcs/interface/render_utils.c \
              ./srcs/interface/drawboard.c \
              ./srcs/interface/get_piece.c

all: $(NAME)

$(MLX):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		git clone https://github.com/42Paris/minilibx-linux.git $(MLX_DIR); \
	fi
	@$(MAKE) -C $(MLX_DIR)

$(STOCK_BIN):
	@if [ ! -d "$(STOCK_DIR)" ]; then \
		git clone https://github.com/official-stockfish/Stockfish.git $(STOCK_DIR); \
	fi
	cd $(STOCK_DIR)/src && $(MAKE) -j profile-build && mv stockfish ../../
	@rm -rf $(STOCK_DIR)

$(NAME): $(MLX) $(STOCK_BIN) $(SRCS_DIR)
	$(CC) $(CFLAGS) $(SRCS_DIR) -o $(NAME) $(LDFLAGS)

clean:
	rm -rf objs

fclean: clean
	rm -rf $(NAME)
	rm -rf $(MLX_DIR)
	rm -rf $(STOCK_BIN)
	rm -rf $(STOCK_DIR)

re: fclean all

.PHONY: all clean fclean re fclean all
