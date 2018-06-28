CUDAPATH=/opt/cuda

CC	:= gcc

RM	:= rm -rf

CFLAGS	+= -Iincludes -I/opt/cuda/include

SRCS	:= $(shell find srcs -type f -name "*.c")

KERSRCS	:= $(shell find srcs -type f -name "*.cu")

LDFLAGS := -L$(CUDAPATH)/lib64 -lcublas -lcudart -lstdc++

OBJS	:= $(SRCS:.c=.o) $(KERSRCS:.cu=.o)

NAME	:= Gru

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

%.o : %.cu
	$(CUDAPATH)/bin/nvcc -c $(CFLAGS) -o $@ $<

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all re clean fclean
