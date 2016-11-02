CC = gcc
CFLAGS = -std=gnu99

EXEC = web

SRC =   simple_WebServer.c tcp_socket.c
OBJ = $(SRC:%.c=%.o)

all: $(EXEC)
$(EXEC): $(OBJ)                           
	$(CC) $^ -o $@

%.o: %.c 
	$(CC) -c $(CFLAGS) $< -o $@
.PHONY: clean
clean:
	@ rm  *.o* $(EXEC)
