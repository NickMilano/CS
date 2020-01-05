Crypto: Crypto.o Key.o Stats.o
	gcc Crypto.o Key.o Stats.o -o Crypto

Crypto.o: Crypto.c Key.c
	gcc -std=c99 -pedantic -Wall -c Crypto.c

Key.o: Key.c
	gcc -std=c99 -pedantic -Wall -c Key.c

Stats.o: Stats.c
	gcc -std=c99 -pedantic -Wall -c Stats.c
