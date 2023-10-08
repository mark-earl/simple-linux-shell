1. Should I include ulimit -u 10 in my makefile?

```makefile
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

run: ulimit_run
	@./shell.out

ulimit_run:
	@ulimit -u
```

2. Is it okay that my implementation of `E` just calls the `echo` function?
3. Is my implementation of the `S` command okay? Is the shutdown behavior okay (have to close firefox before the shell will exit)?
4. Do you want more documentation than what I have provided?
