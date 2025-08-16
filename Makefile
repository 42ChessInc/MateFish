NAME= autoMate

CC = cc

CFLAGS = -Wall -Werror -Wextra -Iinclude -lSDL2

SRCS_DIR = ./srcs/main.c

OBJS_DIR = objs

INC_DIR = include

all: $(NAME)

fclean: clean
	rm -rf $(NAME)
clean:
	rm -rf $(OBJS_DIR)

$(NAME): $(SRCS_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(SRCS_DIR)

