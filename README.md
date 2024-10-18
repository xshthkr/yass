# YASS - Yet Another Stupid Shell

A simple minimal shell written in C. This simple C program reads a stream of input from the user, parses it, and forks a child process to execute the user's commands.

## How to compile and run

1. Clone the repository:

    ```shell
    git clone https://github.com/xshthkr/yass.git
    ```

2. Navigate to the project directory and compile the source code:

    ```shell
    cd yass
    make
    ```

3. Run the compiled binary from the `bin` folder:

    ```shell
    cd bin
    ./yass
    ```

Once YASS is running, you will see a prompt `yass >`. Enter commands as you normally would with any other shell. To exit the shell, type `exit`.

## How it works

### Commands

Commands are stored in the form of a struct. The struct `command` includes:

- `char* name` - the name of the command.
- `char** args` - an array of arguments passed to the command.
- `int argc` - the number of arguments passed.

### Receiving Input

The user input is read using the `read_line()` function. This function reads a line from `stdin` and reports errors if any.

### Parsing Input

The user input is then parsed and split into tokens separated by tabs, spaces, and newline delimiters. Memory is allocated for the arguments using `malloc()`, and if the arguments exceeds the buffer size, the buffer is dynamically expanded using `realloc()`.

### Execution

The command along with its arguments are executed by forking to create a child process using `fork()`. The child process is replaced by a process executing the command using `execvp()`. The parent process waits for the child process to finish executing before being ready to receive the next command using `wait() to avoid zombie process.`
