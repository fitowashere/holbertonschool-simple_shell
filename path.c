#include "shell.h"

/**
 * path- Extracts paths from the PATH environment variable
 * @env: stores the variable
 * Return: A pointer to an array of strings containing the paths
 */
char *path(char **env)
{
	int counter = 0;
	char *path;
	char **new_path;

	while (env[counter])
	{
		if (strncmp(env[counter], "PATH", 4) == 0)
			/**
			 * checks if the current environment variable starts with "PATH".
			 * compares the first 4 characters of the environment variable
			 * with the string "PATH". If the condition is true, it means
			 * the current environment variable is the one containing the path.
			 */
		{
			path = strdup(env[counter]);
			new_path = separate_commands(path, "=");
			/**
			 * This function separates the environment variable into tokens
			 * using the "=" delimiter and returns an array of strings
			 */
			free(path);
			path = strdup(new_path[1]);
			/**
			 * duplicate this string, and the result
			 *is assigned to the  path  variable.
			 */
		}
		counter++;
	}
	free_array(new_path);
	return (path);
}