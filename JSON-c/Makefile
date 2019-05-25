
NAME = libjsonchecker.a

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

CC = gcc

.PHONY: all clean fclean re

.NOTPARALLEL: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	@ar rc $(NAME) $(OBJS)

clean:
	@/bin/rm -f $(wildcard *.o)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all