#include "shell.h"

/**
 * execution- executes commands
 * @commands: array of commands
 * @env: The environment variables
 * Return: 1 on success 0 on failure
 */
int execution(char **commands, char **env)
{
	char *path_token = NULL, **cmd = NULL;

	if (access(commands[0], X_OK) != 0)
	{ /*checks if it's not already created and if it's executable*/
		path_token = path(env);
		cmd = separate_commands(path_token, ":");
		free(path_token);
		commands[0] = add_path(commands, cmd);
		free_array(cmd);

		if (access(commands[0], X_OK) != 0)
		{
			fprintf(stderr, "%s: command not found\n", commands[0]);
			/*display a more specific error message*/
			free_array(commands);
			return (0);
		}
	}

	create_child_process(commands, env, commands[0]);
	/* Call the create_child_process function */

	free_array(commands);
	return (1);
}