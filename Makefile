NAME := pipex
CC := gcc
CFLAGS := -Wall -Wextra -Werror -Iheaders/

SOURCE := srcs/*.c
LIBFT := Libft/*.c

all:	
		$(CC) $(CFLAGS) $(LIBFT) $(SOURCE) -o $(NAME)
	 

clean:

fclean: clean
		rm -rf $(NAME) 

re: fclean all

.PHONY: all clean fclean re