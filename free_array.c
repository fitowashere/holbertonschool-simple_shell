#include "shell.h"

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