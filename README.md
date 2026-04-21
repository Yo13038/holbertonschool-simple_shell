 ## README of the group project simple_shell

A custom implementation of a Unix command line interpreter, built from scratch in C.

![C](https://img.shields.io/badge/C-gnu89-blue)
![Linux](https://img.shields.io/badge/Linux-Ubuntu-orange)
![Project](https://img.shields.io/badge/Project-Holberton-success)

##  Table of Contents

<details>
<summary> Click to expand</summary>

<br>

*  [Description](#description)
*  [Features](#features)
*  [Project Structure](#️project-structure)
*  [Installation](#️installation)
*  [Compilation](#️compilation)
*  [Usage](#️usage)
*  [Manual](#manual)
*  [Limitations](#️limitations)
*  [Valgrind](#valgrind)
*  [Flowchart](#flowchart)
*  [Authors](#authors)

</details>

##  Description

`simple_shell` is a custom implementation of a basic Unix shell.

It reads user input, parses commands, searches executables in the `PATH`, and runs them using `fork`, `execve`, and `wait`.

This project was completed in pairs as part of the Holberton School curriculum

##  Features

- Interactive mode
- Non-interactive mode
- Execution of commands with full path<br>
  Example: `/bin/ls`
- Execution of commands using `PATH`<br>
  Example: `ls`
- Command parsing into arguments
- Builtin `exit`
- Builtin `env`
- Handles empty lines
- Handles `EOF` (`Ctrl + D`)

##  Project Structure

```bash
.
├── main.h
├── main.c
├── loop.c
├── builtins.c
├── free_utils.c
├── parser.c
├── path.c
├── execute.c
├── string_utils.c
├── man_1_simple_shell
├── AUTHORS
└── README.md
```

##  Installation

Clone the repository and move into the project directory:
```
git clone <https://github.com/Yo13038/holbertonschool-simple_shell.git>
cd holberton-simple_shell
```

##  Compilation

Compile the project with:
```
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

##  Usage

Run the shell in interactive mode:
```
($) ./hsh
($) /bin/ls
($) ls -l
($) env
($) exit
```

Run the shell in non-interactive mode:
```
($) echo "/bin/ls" | ./hsh
($) printf "env\nexit\n" | ./hsh
```

## Manual

To open the manual page, run:

```bash
($) man ./man_1_simple_shell
```

##  Limitations

This version of simple_shell is a basic shell and does not support:

- Pipes
- Redirections
- Command chaining
- Wildcards
- Aliases
- Advanced environment management
- Signals beyond the project requirements

##  Valgrind

You can test memory leaks with:
```
($) printf "env\n/bin/ls\nqwerty\nexit\n" | valgrind --leak-check=full --show-leak-kinds=all ./hsh
```

Expected goal:
```
==13872== HEAP SUMMARY:
==13872==     in use at exit: 0 bytes in 0 blocks
==13872==   total heap usage: 47 allocs, 47 frees, 8,075 bytes allocated
==13872==
==13872== All heap blocks were freed -- no leaks are possible
==13872==
==13872== For lists of detected and suppressed errors, rerun with: -s
==13872== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

##  Flowchart

![Description](https://github.com/Yo13038/holbertonschool-simple_shell/blob/jo/flowchart-simple_shell.png)

##  Authors
| Yohan Lages | [Yo13038](https://github.com/Yo13038) |<br>
| Jonathan Martin | [John-Natty](https://github.com/John-Natty) |

Students at Holberton School, Toulouse.
