# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdovhopo <mdovhopo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/19 11:58:45 by domelche          #+#    #+#              #
#    Updated: 2019/04/24 12:47:59 by mdovhopo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RT

CC = gcc
#CFLAGS = -Wall -Wextra -Werror

# finding all sources and cutting 'src/' prefix
SRCS = $(shell find src -name '*.c' | cut -c 5-)

OBJS = $(addprefix obj/,$(SRCS:.c=.o))

# external libraries
LDFLAGS =	$(LIBSDL) -lm \
			libftprintf/libftprintf.a \
			libpnt/libpnt.a \
			JSON-c/libjsonchecker.a
INCLDES =	$(INCSDL) \
			-I inc \
			-I libftprintf \
			-I libpnt \
			-I JSON-c
# src/dir/source.c -> obj/dir
OBJ_DIR =	$(shell find src -name '*.c' | cut -c 5- | cut -f1 -d'/' | uniq\
| sed -e 's/^/obj\//')

ifeq ($(shell uname -s), Darwin)
INCSDL =	-I frameworks/SDL2.framework/Headers/ \
			-I frameworks/SDL2_image.framework/Headers/
LIBSDL =	-F ./frameworks -rpath ./frameworks -framework SDL2\
			-F ./frameworks -rpath ./frameworks -framework SDL2_image
endif
ifeq ($(shell uname -s), Linux)
LIBSDL =	-lSDL2_image -lSDL2 -pthread
endif

.PHONY: all name dirs clean fclean re

.NOTPARALLEL: all name dirs clean fclean re

all: dirs
	@$(MAKE) -C libftprintf
	@$(MAKE) -C libpnt
	@$(MAKE) -C JSON-c
	@$(MAKE) name

dirs: $(OBJ_DIR)
	@mkdir -p screenshots

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

name: $(NAME)

obj/%.o: src/%.c
	$(CC) $(CFLAGS) $(INCLDES) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
	@/bin/rm -f $(OBJS)
	@$(MAKE) clean -C libftprintf
	@$(MAKE) clean -C libpnt
	@$(MAKE) clean -C JSON-c

fclean:
	@/bin/rm -rf obj
	@/bin/rm -f $(NAME)
	@$(MAKE) fclean -C libftprintf
	@$(MAKE) fclean -C libpnt
	@$(MAKE) fclean -C JSON-c

re: fclean all
