NAME     = ft_irc

SRCS     := $(shell find -type f -name '*.cpp')
SRC_DIR = src
SRC_SUBFOLDERS = client cmd utils


OBJS_DIR = obj
OBJS_P := $(foreach folder, $(SRC_SUBFOLDERS),$(patsubst ./$(SRC_DIR)/$(folder)/%.cpp, ./$(OBJS_DIR)/%.o,$(SRCS)))

DIRS     = obj

HEADERS  = ./includes

CC       = g++
RM       = rm -f
CFLAGS   = -I $(HEADERS) -Wall -Wextra -std=c++98

all:
	echo $(OBJS_P)

#$(NAME): $(OBJS)
#	$(CC) $(OBJS) $(CFLAGS) -o $(NAME)
#
#$(OBJS): $(SRCS) | $(DIRS)
#	$(CC) $(CFLAGS) -c -o $@ $<
#
#$(DIRS):
#	mkdir -p $(DIRS)
#
#clean:
#	rm -rf $(OBJS_DIR)
#
#fclean:
#	rm -rf $(OBJS_DIR) $(NAME)
#
#re: fclean all
#
#.PHONY: all clean fclean re
