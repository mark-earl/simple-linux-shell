# makefile for simple-linux-shell
# Refer to README.md for build instructions

CC = gcc
CFLAGS = -Wall

all: shell.out

shell.out: main.c
	$(CC) $(CFLAGS) -o $@ $<

run: shell.out
	./shell.out

clean:
	rm -f shell.out

.PHONY: clean


# NOTE: I did not include a ulimit command because on all platoforms that I tested
# I kept getting an error when running the -u argument with ulimit. This shell is
# well tested, it is unlikely a fork bomb will occur, just don't go crazy with a
# script that will overload this shell with commands. Follow the provided ones in
# the man page, and everything should be fine
