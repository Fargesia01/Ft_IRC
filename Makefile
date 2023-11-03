SRCS	=	src/main.cpp src/rpl.cpp src/server.cpp src/client.cpp

OBJS	=	${SRCS:.cpp=.o}

FLAGS	=	-Wall -Wextra -Werror -std=c++98

NAME	=	irc

${NAME}:	${OBJS}
				c++ ${FLAGS} ${OBJS} -o ${NAME}

all:		${NAME}

clean:
				rm -rf ${OBJS}

fclean:		clean
				rm -rf ${OBJS} ${NAME}

re:		fclean all

.PHONY:		all clean fclean re