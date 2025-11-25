# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
NAME = pixelstrip

# Source files
SRCS = pixelstrip.c
OBJS = $(SRCS:.c=.o)

# Header
HEADER = pixelstrip.h

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "✓ Compilation successful!"

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	@echo "✓ Object files cleaned"

fclean: clean
	rm -f $(NAME)
	@echo "✓ Executable cleaned"

re: fclean all

.PHONY: all clean fclean re
