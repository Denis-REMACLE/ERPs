CC = gcc
CFLAGS = -Wall -Wextra -Werror -Wstrict-prototypes -Wno-unused-parameter -lm
RM = rm -f
NAME = ERPs
SRC = *.c

all:
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:
	$(RM) $(NAME)

re: clean all
