#include "shell.h"

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