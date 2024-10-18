# YASS - Yet Another Stupid Shell

A simple minimal shell written in C. This simple C program reads a stream of input from the user, parses it, and forks a child process to execute the user's commands.

## How to compile and run

Clone this repository.

```shell
git clone https://github.com/xshthkr/yass.git
```

Run the `Makefile` in the directory to compile source code.

```shell
cd yass
make
```

Run the compiled binary in the `bin` folder.

```shell
cd bin
./yass
```

## How it works

### Commands

Commands are stored in the form of a struct. The struct `command` holds the name of the command and an array and number of arguments passed.

### Receiving Input

The user input is read using the `read_line()` function. This function reads a line from `stdin` returns it.

### Parsing Input

The user input is then parsed into tokens separated by tabs, spaces, and newline delimiters. Memory is allocated for the arguments using `malloc`, and if the arguments exceeds the buffer size, the buffer is dynamically expanded using `realloc`.

### Execution

The command along with its arguments are executed by forking to create a child process. The parent process waits for the child process to finish executing before being ready to receive the next command.