NAME = server

CC = gcc

CFLAGS = -Wall -Wextra -g

SRC =	src/server.c

OBJ = $(SRC:.c=.o)


CLIENT_NAME = client

CLIENT_SRC = src/client.c

CLIENT_OBJ = $(CLIENT_SRC:.c=.o)

LIB = ft

LIBDIR = libft

all : $(NAME) $(CLIENT_NAME)

src/%.o : src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJ) $(CLIENT_OBJ)
	make -C libft
	$(CC) $(CFLAGS) $(OBJ) -L $(LIBDIR) -l  $(LIB) -o $(NAME)
	$(CC) $(CFLAGS) $(CLIENT_OBJ) -L $(LIBDIR) -l  $(LIB) -o $(CLIENT_NAME)

clean :
	make clean -C libft
	rm -f $(OBJ) $(CLIENT_OBJ)

fclean : clean
	make fclean -C libft
	rm -f $(NAME) $(CLIENT_NAME)

re : fclean all