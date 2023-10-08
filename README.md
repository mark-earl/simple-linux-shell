# A Simple Linux Shell

## Build Instructions
1. Ensure that you are in the source directory
```bash
/simple-linux-shell$
```
2. `make`
```bash
/simple-linux-shell$ make
```

3. `make run`
```bash
/simple-linux-shell$ make run
```
4. You should now be able to interact with a very basic linux shell
```bash
linux(mpe12)|>
```

## How to Use
The simple linux shell supports a set of internal commands. Here's how to use them:

* `C file1 file2`: Copy the contents of file1 to file2 without deleting file1.
* `D file`: Delete the specified file.
* `E comment`: Display the provided comment on the screen. If no argument is given, it will issue a new prompt.
* `H`: Display a user manual with information on how to use the shell.
* `L`: List the contents of the current directory.
* `M file`: Create a new text file using a text editor.
* `P file`: Print the contents of the named file on the screen.
* `Q`: Quit the shell.
* `S`: Launch a web browser as a background process.
* `W`: Clear the screen.
* `X program`: Execute the specified program.

Please note that all commands are case-sensitive. If you want to execute external commands not listed here, you can simply enter them, and the shell will attempt to run them using execvp().

## Functions in the Shell
The Simple Linux Shell contains the following functions:

* Input and command parsing
    * `parseCommand()`
    * `readCommand()`
* Execution of internal commands using `execvp()` and process management using `fork()` and `wait()`.
* Handling of internal commands
    * `cp`
    * `rm`
    * `printf`
    * `man`
    * `pwd`
    * `ls -l`
    * `nano`
    * `more`
    * `firefox`
    * `clear`
    * `wipe`

## Citations
In the development of this project, the following resources were referenced:

* [POSIX man pages](https://man7.org/linux/man-pages/man3/execvp.3.html) for information on system calls.
* Various online forums and tutorials for assistance with POSIX system calls.
* Linux command documentation for equivalent commands used in the shell.
