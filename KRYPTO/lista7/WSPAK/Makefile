CC=gcc
CFLAGS=-Wall -g
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
EXEC=main.out

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

connect:
	telnet localhost 7777

clean:
	rm -f $(OBJ) $(EXEC)

