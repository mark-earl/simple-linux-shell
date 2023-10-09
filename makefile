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

run: chmod_run
	@./shell.out

chmod_run:
	@chmod +x ./shell.out
