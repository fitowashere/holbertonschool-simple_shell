#include "shell.h"

/**
 * create_child_process- creates and execute the child process
 * @command: the commands to execute
 * @env: the enviroment variables
 * @full_commands: stores the full command path
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
		free_array(command);
		free(full_commands);
		exit(EXIT_FAILURE);	/* Exit child process with failure status */
	}
	else
	{
		wait(NULL); /* Parent process waits for the child process to complete */
	}
}

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

/**
 * separate_commands- separates the string of commands into tokens
 * @commands: stores commands
 * @separater: stores the character used as a seperator between comands
 * Return: array of tokens
 */

char **separate_commands(char *commands, char *separater)
{
	char *token = NULL;
	char **tokens = NULL;
	int token_count = 0;

	tokens = malloc(sizeof(char *) * 10);

	if (tokens == NULL)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	token = strtok(commands, separater); /*separates the comands into tokens*/

	while (token)
	{
		/*Store current token in the tokens array */
		tokens[token_count] = strdup(token);
		if (tokens[token_count] == NULL)
		{
			perror("Memory allocation failed");
			free_tokens(tokens);
			exit(EXIT_FAILURE);
		}
		token_count++; /* Increment the token count */

		token = strtok(NULL, separater);
		/*Get the next token from the command string */

	}

	tokens[token_count] = NULL;
	/**
	 * After the loop finishes, it means all
	 * the tokens have been extracted. The
	 * tokens[token_count] element is set to
	 * NULL to mark the end of the array.
	 */
	/*free_tokens(tokens); this crashes the hell out of the program*/
	free(token);
	return (tokens);
}

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
