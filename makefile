# makefile for simple-linux-shell
# Refer to README.md for build instructions

CC = gcc
FLAGS = -Wall

all: shell.out clean

shell.out: main.cpp
	@${CC} ${FLAGS} main.cpp -o shell.out

clean:
	@rm -f *.o
	@rm -f *~
	@rm -f \#*

run:
	@chmod +x ./shell.out
	@./shell.out

# NOTE: I did not include a ulimit command because on all platoforms that I tested
# I kept getting an error when running the -u argument with ulimit. This shell is
# well tested, it is unlikely a fork bomb will occur, just don't go crazy with a
# script that will overload this shell with commands. Follow the provided ones in
# the man page, and everything should be fine
