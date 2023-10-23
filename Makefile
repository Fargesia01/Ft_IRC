SRCS     = src/main.cpp src/cmd/parser.cpp src/utils/split.cpp
SRCS_DIR = src
OBJS_DIR = obj
OBJS     = $(patsubst $(SRCS_DIR)/%.cpp,$(OBJS_DIR)/%.o,$(SRCS))
DIRS     = obj
HEADERS  = includes
NAME     = ft_irc
CC       = g++
RM       = rm -f
CFLAGS   = -I $(HEADERS) -Wall -Wextra -std=c++98

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.cpp | $(DIRS)
	$(CC) -c $(CFLAGS) $< -o $@

$(DIRS):
	mkdir -p $(DIRS)

clean:
	$(RM) -r $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

