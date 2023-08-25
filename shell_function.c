#include "shell.h"

/**
 * create_child_process- creates the child
 * @command: the commands to execute
 * @env: the enviroment variables
 * @full_commands: stores the commands with full path
 */

void create_child_process(char **command, char **env, char *full_commands)
{
	pid_t child_pid;

	child_pid = fork(); /* Create a child process */
	if (child_pid == -1)
	{
		perror("Child process failed"); /* Print error message if fork fails */
		return;
	}
	if (child_pid == 0)
	{
		execve(full_commands, command, env); /* Execute the command using execve */
		perror("Execution failed"); /* Print an error message if execve fails */
		exit(EXIT_FAILURE);	/* Exit child process with failure status */
	}
	else
	{
		wait(NULL); /* Parent process waits for the child process to complete */
	}
}
