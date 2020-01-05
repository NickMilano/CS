CC=gcc
SRC_FILES=*.c
OBJ_FILES=*.o
OPTS=-g -pedantic -Wall -I.
EXE=prog1

build: $(SRC_FILES)
	$(CC) $(OPTS) -lm  -o $(EXE) $(SRC_FILES)

.PHONY: clean

clean:
	rm -f $(EXE) $(OBJ_FILES)
