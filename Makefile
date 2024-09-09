CC = clang
CFLAGS = -pthread -g -Wall -Wextra -Wpedantic 

all: client server

client: client.o
	$(CC) $(CFLAGS) $^ -o $@

server: server.o handler.o queue.o
	$(CC) $(CFLAGS) $^ -o $@

client.o: client.c
	$(CC) $(CFLAGS) -c $< -o $@

server.o: server.c queue.h handler.h
	$(CC) $(CFLAGS) -c $< -o $@

handler.o: handler.c handler.h
	$(CC) $(CFLAGS) -c $< -o $@

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o client server

.PHONY: clean
