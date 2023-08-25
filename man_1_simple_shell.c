.TH SIMPLE_SHELL 1 "August 25, 2023" Linux "USER MANUALS"
.SH NAME

simple_shell - command language interpreter

.SH SYNOPSIS
.B #include\ "shell.h"

.B Interactive Mode: ./hsh

.B Non-Interactive Mode: [COMMAND]... | ./hsh

.SH COMPILE
 gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

 .SH OPTIONS
.TP
.B System calls to recive without any arguments, such as:
.P
    Example - |  ls | pwd | help | cd

.B System calls to recive WITH arguments, such as:
.P
    Example - | ls -la | cd .. | mkdir ...[DIRECTORY]

.SH DESCRIPTION
Our simple_shell program is capable of receiving input by the user at the command line.
The program reads the input, splits it into arguments, and executes the command being provided.

.SS SHELL BUILTIN COMMANDS
    env - prints environmental variables
    exit - exits out of simple shell and returns to users original shell
    $$ - gets process id


.SS SHELL USER MANUALS

.SH FILES
\shell.h\
    P: Header file containing function prototypes, macros, and libraries.

\fBseparate_commands.c\
    P: Tokenizes user input into separate commands.

\handle_commands.c\  
    P: Processes and interprets user commands or external executable files.

\free_array.c\
    P: Contains functions to free dynamically allocated memory.

\builtin_commands.c\
    P: Implements built-in commands.

\add_path.c\
    P: Adds directories to the shells search path.

\execution.c\
    P: Handles execution of external commands.

\create_child_process.c\
    P: Creates and manages child processes.

.SH RETURN
Return "-1" on error with prompted error line message or "0" on success

.SH BUGS
No known bugs.

.SH AUTHOR
Sweety Marie Castro & Hector Rodriguez Lopez

.SH COPYRIGHT
\SIMPLE_SHELL\ P Copyright, 2023

