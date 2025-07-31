NAME= autoMate

CC = cc

CFLAGS = -Wall -Werror -Wextra -Iinclude

SRCS_DIR = ./srcs/main.c

OBJS_DIR = objs

INC_DIR = include

all: $(NAME)

$(NAME): $(SRCS_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(SRCS_DIR)

