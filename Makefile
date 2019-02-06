# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: domelche <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/19 11:58:45 by domelche          #+#    #+#              #
#    Updated: 2019/01/22 15:39:23 by domelche         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RT

LIBFT_NAME = libft.a
LIBFT_PATH = libft/$(LIBFT_NAME)
LIBFT_INC  = -Ilibft

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

HEAD = rtv1.h

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

$(NAME): $(OBJ)
	@$(MAKE) -C libft
	@$(MAKE) -C libpnt
	@$(CC) $(CFLAGS) $(SRCS) -o $(NAME) \
		$(LIBFT_PATH) $(LIBMLX_PATH) $(LIBPNT_PATH) \
		$(SDL_LNK) $(SDL_IMG_LNK)

clean:
	@/bin/rm -f src/*/*.o
	@$(MAKE) clean -C libft
	@$(MAKE) clean -C minilibx
	@$(MAKE) clean -C libpnt

fclean: clean
	@/bin/rm -f $(NAME)
	@/bin/rm -f $(LIBFT_PATH)
	@/bin/rm -f $(LIBMLX_PATH)
	@/bin/rm -f $(LIBPNT_PATH)

re: fclean all
