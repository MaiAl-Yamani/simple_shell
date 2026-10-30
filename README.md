# Simple Shell

A Unix-style command-line shell implemented in C as part of the ALX Software Engineering Programme.

## Overview

The project explores how a shell reads commands, resolves executable paths, and manages program execution. The implementation is organized into modules for command processing, built-in commands, environment handling, string utilities, and error reporting.

## Implementation

- Command input and parsing
- Command execution and path resolution
- Built-in command handling
- Environment variable management
- Error handling and helper utilities

## Project Structure

- `hsh_main.c` — shell entry-point logic
- `builtin.c`, `builtin2.c` — built-in command handlers
- `handle_path.c` — path handling
- `env.c`, `env_2.c` — environment utilities
- `shell.h` — shared declarations

## Build & Run

Compile the C source files with GCC, then run the resulting shell executable:

```bash
gcc -Wall -Wextra -Werror -pedantic *.c -o hsh
./hsh
```

## Technologies

C · Unix/Linux · GCC · System Programming

## Related Repositories

- [Low-Level Programming](https://github.com/MaiAl-Yamani/alx-low_level_programming)
- [Custom printf Implementation](https://github.com/MaiAl-Yamani/printf)
