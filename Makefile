CC = gcc
CFLAGS = -Wall -Wextra -Werror -Wstrict-prototypes -std=c99
RM = rm -f
NAME = ERPs
SRC = *.c

all:
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:
	$(RM) $(NAME)

re: clean all
