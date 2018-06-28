CUDAPATH=/opt/cuda


CC	:= gcc

RM	:= rm -rf

CFLAGS	+= -Iincludes -I/opt/cuda/include

SRCS	:= $(shell find srcs -type f -name "*.c")

KERSRCS	:= $(shell find srcs -type f -name "*.cu")

LDFLAGS := -L$(CUDAPATH)/lib64 -lcublas -lcudart

OBJS	:= $(SRCS:.c=.o)

NAME	:= Gru

all: $(NAME)

$(NAME): $(OBJS) kernels
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

kernels:
	$(CUDAPATH)/bin/nvcc -c $(CFLAGS) $(KERSRCS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all re clean fclean
