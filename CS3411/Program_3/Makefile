all: reserver reclient

reserver: reserver.c
	gcc -pedantic -w -o reserver  reserver.c

reclient: reclient.c
	gcc -pedantic -w -o reclient reclient.c

.PHONY: clean

clean:
	rm -f reserver reclient

