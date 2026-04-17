 ## README of the group project simple_shell

A custom implementation of a Unix command line interpreter, built from scratch in C.

![C](https://img.shields.io/badge/C-gnu89-blue)
![Linux](https://img.shields.io/badge/Linux-Ubuntu-orange)
![Project](https://img.shields.io/badge/Project-Holberton-success)

##  Table of Contents

<details>
<summary> Click to expand</summary>

<br>

*  [Description](#-description)
*  [Features](#-features)
*  [Project Structure](#️-project-structure)
*  [Installation](#️-installation)
*  [Compilation](#️-compilation)
*  [Usage](#️-usage)
*  [Manual](#-manual)
*  [Limitations](#️-limitations)
*  [Valgrind](#-valgrind)
*  [Flowchart](#-flowchart)
*  [Authors](#-authors)

</details>

##  Description

`simple_shell` is a custom implementation of a basic Unix shell.

It reads user input, parses commands, searches executables in the `PATH`, and runs them using `fork`, `execve`, and `wait`.

This project was completed in pairs as part of the Holberton School curriculum

##  Features

- Interactive mode
- Non-interactive mode
- Execution of commands with full path  
  Example: `/bin/ls`
- Execution of commands using `PATH`  
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

NEANT

##  Compilation

```
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

##  Usage

NEANT

##  Manual

Use the following command to access the manual:

man ./man_1_simple_shell

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

NEANT

##  Flowchart

NEANT

##  Authors
| Yohan Lages | [Yo13038](https://github.com/Yo13038) |<br>
| Jonathan Martin | [John-Natty](https://github.com/John-Natty) |

Students at Holberton School, Toulouse.
