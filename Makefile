
CC=gcc
CFLAGS=-Wall -Wextra
BIN=text-formatter

.PHONY: all clean

all: $(BIN)

run: $(BIN)
	./$<

clean:
	rm $(BIN)

#----------------------------------------------------------------

$(BIN): src/main.c
	$(CC) $(CFLAGS) -o $@ src/main.c

