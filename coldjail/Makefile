CC=gcc
CFLAGS=-Iinclude -Wall -Wextra

SRC=$(wildcard src/*.c)
OBJ=$(SRC:.c=.o)

coldjail: $(OBJ)
	$(CC) $(OBJ) -o coldjail

clean:
	rm -f src/*.o coldjail

