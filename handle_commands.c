#include "shell.h"

/**
 * handle_commands- Execute commmands or print environment variables
 * @commands: array of commands
 * @env: the enviroment variables
 */
void handle_commands(char **commands, char **env)
{
	int counter = 0;

	if (commands[0] != NULL)
	{
		if (strcmp(commands[0], "env") == 0)
		{
			while (env[counter])
			{
				write(1, env[counter], strlen(env[counter]));
				write(1, "\n", 1);
				counter++;
			}
			free_array(commands);
			return;
			/**
			 * If the first token is "env", the code enters a loop to
			 * print the environment variables ( env ) to the console,
			 * each on a new line after that it will free memory allocated
			 * for the array, and the program continues to the next iteration
			 * of the loop.
			 */
		}
		if (builtin_commands(commands) == 1)
		{
			execution(commands, env);
		}
		/*cheacks if its built in comand and excecute it*/

	}
	else
		free(commands);
}