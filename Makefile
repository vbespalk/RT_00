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

NAME	=	RT

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
SRCS	=	$(wildcard src/*/*.c)
OBJS	=	$(SRCS:.c=.o)
DIRS	=	./screenshots/

INC		=	-I inc -I libftprintf -I libpnt -I JSON-c \
			-I frameworks/SDL2.framework/Headers/ \
			-I frameworks/SDL2_image.framework/Headers/

LLIBS	=	-lftprintf \
			-ljsonchecker \
			-lpnt \
			-framework SDL2 \
			-framework SDL2_image

LIBS	=	-L libftprintf \
			-L libpnt \
			-L JSON-c \
			-F ./frameworks -rpath ./frameworks \
			-F ./frameworks -rpath ./frameworks

.PHONY: all clean fclean re

.NOTPARALLEL: all clean fclean re

all: $(NAME) $(DIRS)

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@ 

$(NAME): $(OBJS)
	@$(MAKE) -C libftprintf
	@$(MAKE) -C libpnt
	@$(MAKE) -C JSON-c
	@$(CC) -o $(NAME) $(OBJS) $(LIBS) $(LLIBS)

$(DIRS):
	mkdir -p $(DIRS)

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
