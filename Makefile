SRCS	= src/main.cpp src/cmd/parser.cpp src/utils/split.cpp

OBJS 	= $(SRCS:.cpp=.o)

NAME	= ft_irc

CC	= c++

RM	= ft_irc

CFLAGS	= -Wall -Wextra -Werror -std=c++98

$(NAME): $(OBJS)
	 $(CC) $(CFLAGS) -o $(NAME) $(OBJS)

all:	$(NAME)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:		fclean all

.PHONY: all clean fclean re
