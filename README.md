# get_next_line

This project is part of the 42 school curriculum and focuses on reading a file line by line using a file descriptor in C. The goal is to implement a function `get_next_line()` that reads and returns one line from a given file descriptor, handling memory and buffer management manually and using only read(), malloc() and free().

## Project Description

The `get_next_line` function allows you to read from a file descriptor one line at a time. It is designed to work with different file descriptors, handles buffer limitations, and returns each line with the newline character (`\n`) when present.

Function prototype:

```c
char *get_next_line(int fd);
```

## Mandatory Requirements

- Reads from a file descriptor line by line on each call.
- Returns a full line (including the \n), or NULL if there’s nothing more to read or an error occurs.
- Works with both files and standard input.
- Must compile with and without the -D BUFFER_SIZE=n flag.
- Allowed functions: read(), malloc(), free().

Key Concepts

- Uses a static variable to preserve reading state between function calls.
- Efficient memory management using malloc and free.
- Uses the read() system call with a buffer of defined size.

Compilation

To compile the project:


```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```

You can adjust BUFFER_SIZE to test different performance and behavior cases.

## Files

- get_next_line.c: Core implementation of the function.
- get_next_line_utils.c: Helper functions used by get_next_line.
- get_next_line.h: Header file with the function prototype and necessary includes.

## Bonus

- Handles multiple file descriptors simultaneously.
- Maintains a separate reading state for each file descriptor using only one static variable.

## Example Usage

```c
int fd = open("example_file.txt", O_RDONLY);
char *line;

while ((line = get_next_line(fd)) != NULL)
{
    printf("%s", line);
    free(line);
}
close(fd);
```
