#ifndef shell_h
#define shell_h
#include <unistd.h> / Write, Fork, Execve, Isatty/
#include <stdio.h> / Getline /
#include <string.h> / built in functions /
#include <sys/types.h> / Fork, Wait /
#include <stdlib.h> / Exit /
#include <sys/wait.h> //Wait /


char **separate_commands(char commands, char separater);
int execution(char commands, char env);
void create_child_process(char command, char env, char full_commands);
char path(char **env);
charadd_path(char command_token, char path_token);
int builtin_commands(char commands);
void free_array(char array);
void handle_commands(char commands, char env);


#endif