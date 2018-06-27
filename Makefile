CC	:= gcc

RM	:= rm -rf

CFLAGS	+= -Iincludes -I/opt/cuda/include

SRCS	:= $(shell find srcs -type f -name "*.c")

OBJS	:= $(SRCS:.c=.o)

NAME	:= Gru

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all re clean fclean
