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
CFLAGS = -Wall -Wextra -Werror
SRCS = $(wildcard src/*/*.c)
OBJS = $(SRCS:.c=.o)

INC = -I inc -I libftprintf -I libpnt -I JSON-c \
-I frameworks/SDL2.framework/Headers/ \
-I frameworks/SDL2_image.framework/Headers/

LIBS = libftprintf/libftprintf.a libpnt/libpnt.a JSON-c/libjsonchecker.a








#LIBFT_NAME = libftprintf.a
#LIBFT_PATH = libftprintf/$(LIBFT_NAME)
#LIBFT_INC  = -Ilibftprintf
#
#LIBPNT_NAME = libpnt.a
#LIBPNT_PATH = libpnt/$(LIBPNT_NAME)
#LIBPNT_INC  = -I libpnt
#
#LIBJSON_NAME = libjsonchecker.a
#LIBJSON_PATH = JSON-c/$(LIBJSON_NAME)
#LIBJSON_INC = -IJSON-c
#
#SDL_INC =	-I frameworks/SDL2.framework/Headers/
#SDL_LNK	=	-F ./frameworks -rpath ./frameworks -framework SDL2
#
#SDL_IMG_INC =	-I frameworks/SDL2_image.framework/Headers/
#SDL_IMG_LNK =	-F ./frameworks -rpath ./frameworks -framework SDL2_image
#
#INC	=	-I./inc/
#
## LINUX SDL
#
##SDL_INC		= -I/usr/include/SDL2 -D_REENTRANT
##SDL_LNK		= -lSDL2
##SDL_IMG_LNK = -lSDL2_image
#LFLAGS =
#
#HEAD = rt.h
#
#CFLAGS = -pthread $(LIBFT_INC) $(LIBPNT_INC) $(LIBJSON_INC) $(INC) $(SDL_INC)\
#			$(SDL_IMG_INC)
#
#EFLAGS =
#
## MacOSX flags
#
#FLAGS = -framework OpenGL -framework AppKit
#
#
#
##SDL_LNK		= -lSDL2
##SDL_IMG_LNK = -lSDL2_image
#LFLAGS 		= -pthread -lm




.PHONY: all clean fclean re

.NOTPARALLEL: all clean fclean re

all: $(NAME) 

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@ $(LIBS)

$(NAME): $(OBJS)
	@$(MAKE) -C libftprintf
	@$(MAKE) -C libpnt
	@$(MAKE) -C JSON-c
	@$(CC) -o $(NAME) $(OBJS)

clean:
	@/bin/rm -f $(OBJS)
	@$(MAKE) clean -C libftprintf
	@$(MAKE) clean -C libpnt
	@$(MAKE) clean -C JSON-c

fclean:
	@/bin/rm -f $(OBJS)
	@/bin/rm -f $(NAME)
	@$(MAKE) fclean -C libftprintf
	@$(MAKE) fclean -C libpnt
	@$(MAKE) fclean -C JSON-c

re: fclean all
