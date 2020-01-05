all: client server

client: client.c
	gcc -pedantic -Wall -o client client.c unreliable.c

server: server.c
	gcc -pedantic -Wall -o server server.c unreliable.c

.PHONY: clean

clean:
	rm -f client server

