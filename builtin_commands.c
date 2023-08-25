#include "shell.h"

/**
 * builtin_commands- checks and execute built in commands.
 * @commands: array of commands
 * Return: 0 if the command is a built-in, 1 otherwise.
 */
int builtin_commands(char **commands)
{
	if (strcmp(commands[0], "exit") == 0)
		/*compares the string to check if its exit*/
	{
		free_array(commands);
		exit(0);
	}
	else if (strcmp(commands[0], "$$") == 0)
	{
		fprintf(stderr, "Shell Process ID: %d\n", getpid());
		return (0);
	}
	return (1);
}