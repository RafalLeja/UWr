CC=gcc
CFLAGS=-Wall -g
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
LIBS=-lgnutls 
EXEC=main.out

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS)  -o $@ $^ $(LIBS)

connect:
	 openssl s_client -connect localhost:7777 -ign_eof -showcerts -tls1_3 -CAfile ca_keys/ca_cert.pem

clean:
	rm -f $(OBJ) $(EXEC)

