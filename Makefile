NAME = ft_irc

SRCS = main.cpp \
		client/client.cpp \
		cmd/NICK.cpp \
		cmd/parser.cpp \
		utils/split.cpp

SRCS_DIR = src
SUB_DIR = client cmd utils server

OBJS = $(SRCS:.cpp=.o)
OBJS_DIR = obj

DIRS = obj

_SRCS =  $(addprefix $(SRCS_DIR)/, $(SRCS))
_OBJS = $(addprefix $(OBJS_DIR)/, $(OBJS))

HEADERS = includes

CC = g++
FLAGS = -I $(HEADERS) -Wall -Wextra  -std=c++98

all: $(NAME)

$(NAME): $(_OBJS)
	$(CC) $(_OBJS) $(FLAGS) -o $(NAME)

$(_OBJS): $(OBJS_DIR)/%.o : $(SRCS_DIR)/%.cpp $(DIRS)
	$(CC) -c $(FLAGS) $< -o $@

$(DIRS):
	$(foreach dir, $(SUB_DIR), mkdir -p $(DIRS)/$(dir);)

clean:
	rm -rf $(OBJS_DIR)

fclean:
	rm -rf $(OBJS_DIR) $(NAME)

re: fclean all

.PHONY: all re clean fclean
