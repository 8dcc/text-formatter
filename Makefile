
CC=gcc
CFLAGS=-Wall -Wextra -O3
BIN=text-formatter

.PHONY: all run clean install uninstall

all: $(BIN)

run: $(BIN)
	./$<

clean:
	rm $(BIN)

install: $(BIN)
	install --mode=0755 $< /usr/local/bin/$<

uninstall:
	rm -f /usr/local/bin/$(BIN)

#----------------------------------------------------------------

$(BIN): src/main.c
	$(CC) $(CFLAGS) -o $@ src/main.c

