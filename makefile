# makefile for nqmq-mark-earl
# Refer to BUILD.md for instructions

CC = g++
FLAGS = -std=c++11

all: shell.out clean

shell.out: main.cpp
	@${CC} ${FLAGS} main.cpp -o shell.out

clean:
	@rm -f *.o
	@rm -f *~
	@rm -f \#*

run:
	@./shell.out
