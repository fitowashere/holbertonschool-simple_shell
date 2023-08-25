#include "shell.h"

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
	token = strtok(commands, separater); /*separates the comands into tokens*/

	while (token)
	{

		/*Store current token in the tokens array */
		tokens[token_count] = strdup(token);
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

	return (tokens);
}