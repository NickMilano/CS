all: parent child

parent: dealer.c
	gcc -pedantic -Wall -o dealer dealer.c

child: player.c
	gcc -pedantic -Wall -o player player.c

.PHONY: clean

clean:
	rm -f dealer child
