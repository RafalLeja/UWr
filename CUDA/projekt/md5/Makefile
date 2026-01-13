CC = gcc
CFLAGS = -Wall -O2
TARGET = md5
SRCS := $(wildcard ./src/*.c)
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# $(OBJS): ./src/%.o : ./src/%.c
# 	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)

