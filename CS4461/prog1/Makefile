all: client server

client: client.c
	gcc -pedantic -Wall -o client client.c

server: server.c
	gcc -pedantic -Wall -o server server.c

.PHONY: clean

clean:
	rm -f client server

