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
	
		free_array(commands);
	}
	return (0);
}



/**
 * path- Extracts paths from the PATH environment variable
 * @env: stores the variable
 * Return: A pointer to an array of strings containing the paths
 */
char *path(char **env)
{
	int counter = 0;
	char *path = NULL;
	char **new_path = NULL;

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

/**
 * add_path- Concatenate command with path components.
 * @command_token: The tokenized command.
 * @path_token: The tokenized PATH components.
 * Return: The modified command token.
 */

char *add_path(char **command_token, char **path_token)
{

	char *cmd;
	int token_count = 0;
	int com_tok_len, path_tok_len;

	while (path_token[token_count])
	{
		path_tok_len = strlen(path_token[token_count]);
		com_tok_len = strlen(command_token[0]);
		cmd = (char *) malloc((path_tok_len + com_tok_len + 2) * sizeof(char));
		/*Allocate memory for the null and the "/"*/
		strcpy(cmd, path_token[token_count]); /*Copy the path component into cmd*/
		strcat(cmd, "/");
		strcat(cmd, command_token[0]); /*Concatenate the command*/
		if (access(cmd, X_OK) == 0)
			/*checks if it's not already created and if it's executable*/
		{
			command_token[0] = cmd;
			break;
		}
		free(cmd); /*Free the allocated memory if the command is not found*/
		token_count++;
	}
	return (command_token[0]);
}

/**
 * free_array- free's the arrays
 * @array: stores the array
 */
void free_array(char **array)
{
	int i = 0;


	if (array == NULL)
	{
		return;
	}

	while (array[i])
	{
		free(array[i]);
		i++;
	}

	free(array);
}
