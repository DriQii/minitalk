NAME = server

CC = gcc

CFLAGS = -Wall -Wextra -g

SRC =	server.c

OBJ = $(SRC:.c=.o)

LIB = ft

LIBDIR = libft

all : $(NAME)

src/%.o : src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJ)
	make -C libft
	cp libft/libft.a lib
	$(CC) $(CFLAGS) $(OBJ) -L $(LIBDIR) -l  $(LIB) -o $(NAME)
	@echo "\x1b[92m\nMake is successfully completed\n \x1b[0m"

clean :
	make clean -C libft
	rm -rf $(OBJDIR)$(OBJ)

fclean : clean
	make fclean -C libft
	rm -rf $(NAME)

re : fclean all
