#include "shell.h"

/**
 *main - Entry point of the shell program
 *@ac: The number of command-line arguments.
 *@av: An array of command-line argument strings.
 *@env: The array of environment variables.
 *Return: 0 on success
 */
int main(int ac, char **av, char **env)
{
	char *str = NULL, **commands = NULL;
	size_t len = 0;

	(void)ac; /* Suppress unused parameter warning */
	(void)av; /* Suppress unused parameter warning */

	while (1) /*continuously read and process user input*/
	{
		commands = NULL;
		str = NULL;
		len = 0;

		if (isatty(0))
			write(1, "$ ", 2);
		/**
		 * if returns a non-zero value, it means the
		 * program is running in interactive mode
		 */
		if (getline(&str, &len, stdin) == EOF)
			/*gets users input and handles EOD (cntrD)*/
		{
			free(str); /*free's the allocated memory to str*/
			free_array(commands);
			exit(EXIT_SUCCESS);
		}
		commands = separate_commands(str, " \n");
		/*Separate the input line into separate commands.*/
		free(str);

		handle_commands(commands, env);
	}

	free_array(commands);
	free(str);
	return (0);
}