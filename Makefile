# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: domelche <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/19 11:58:45 by domelche          #+#    #+#              #
#    Updated: 2019/02/19 15:29:24 by domelche         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RT

LIBFT_NAME = libftprintf.a
LIBFT_PATH = libftprintf/$(LIBFT_NAME)
LIBFT_INC  = -Ilibftprintf

LIBPNT_NAME = libpnt.a
LIBPNT_PATH = libpnt/$(LIBPNT_NAME)
LIBPNT_INC  = -Ilibpnt

SDL_INC =	-I frameworks/SDL2.framework/Headers/
SDL_LNK	=	-F ./frameworks -rpath ./frameworks -framework SDL2 

SDL_IMG_INC =	-I frameworks/SDL2_image.framework/Headers/
SDL_IMG_LNK =	-F ./frameworks -rpath ./frameworks -framework SDL2_image 

INC	=	-I ./inc/
SRCS = $(wildcard src/*/*.c)
OBJ = $(SRCS:.c=.o)

HEAD = rt.h

CFLAGS = -pthread $(LIBFT_INC) $(LIBPNT_INC) $(INC) $(SDL_INC) $(SDL_IMG_INC)

EFLAGS =  -Wall -Wextra -Werror
# MacOSX flags

#FLAGS = -lmlx -framework OpenGL -framework AppKit

# Linux flags

# FLAGS = -lmlx -lXext -lX11

CC = gcc



.PHONY: all clean fclean re

.NOTPARALLEL: all clean fclean re

all: $(NAME) 

$(NAME): $(OBJ) ./inc/rt.h
	@$(MAKE) -C libftprintf
	@$(MAKE) -C libpnt
	@$(CC) $(CFLAGS) $(SRCS) -o $(NAME) \
		$(LIBFT_PATH) $(LIBMLX_PATH) $(LIBPNT_PATH) \
		$(SDL_LNK) $(SDL_IMG_LNK)

clean:
	@/bin/rm -f src/*/*.o
	@$(MAKE) clean -C libftprintf
	@$(MAKE) clean -C libpnt

fclean: clean
	@/bin/rm -f $(NAME)
	@/bin/rm -f $(LIBFT_PATH)
	@/bin/rm -f $(LIBPNT_PATH)

re: fclean all
