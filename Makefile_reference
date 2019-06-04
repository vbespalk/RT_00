# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/18 14:12:29 by vbespalk          #+#    #+#              #
#    Updated: 2018/08/18 14:12:31 by vbespalk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	RTv1

# source files
SRC =	main.c\
		check.c\
		init.c\
		parser.c\
		source.c\
		sscene.c\
		matrixes.c\
		render.c\
		vectors.c\
		display.c\
		hook.c\
		key.c\
		light.c\
		intersect.c\
		inverse.c\
		threads.c\
		operations.c

# object files
OBJ		= $(addprefix $(OBJ_DIR),$(SRC:.c=.o))

# directories
SRC_DIR	= ./src/
INC_DIR	= ./includes/
OBJ_DIR	= ./obj/

# compilation flags
CFLAGS	= -Wextra -Werror -Wall

# mlx library
MLX		= ./minilibx/
#MLX_LIB	= $(addprefix $(MLX),mlx.a)
#MLX_INC	= -I $(MLX)
MLX_LNK	= -l mlx -framework OpenGL -framework AppKit

# libft library
FT		= ./libft/
FT_LIB	= $(addprefix $(FT),libft.a)
FT_INC	= -I $(FT)
FT_LNK	= -L $(FT) -l ft

#rules
all: obj $(FT_LIB) $(NAME)

obj:
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	$(CC) $(CFLAGS) $(FT_INC) -I $(INC_DIR) -o $@ -c $<

$(FT_LIB):
	make -C $(FT)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(MLX_LNK) $(FT_LNK) -lm -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)
	make -C $(FT) clean

fclean: clean
	rm -f $(NAME)
	make -C $(FT) fclean
			
re:	fclean all