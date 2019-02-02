# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: domelche <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/19 10:53:22 by domelche          #+#    #+#              #
#    Updated: 2018/09/19 10:53:54 by domelche         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libpnt.a

SRCS = $(wildcard *.c)

OBJ = $(SRCS:.c=.o)

HEAD = libpnt.h

CFLAGS = -Wall -Wextra -Werror

CC = gcc

.PHONY: all clean fclean re

.NOTPARALLEL: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)

clean:
	@/bin/rm -f *.o

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
