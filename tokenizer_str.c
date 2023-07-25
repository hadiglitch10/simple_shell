#include "my_shell.h"

/**
 * split_string - Splits a string into words based on a delimiter
 * @input_str: The input string
 * @delimiter: The delimiter character
 * Return: A pointer to an array of strings, or NULL on failure
 */
char **split_string(char *input_str, char delimiter)
{
	int i, j, k, m, num_words = 0;
	char **word_array;

	/* Check if input string is NULL or empty */
	if (input_str == NULL || input_str[0] == '\0')
	{
		perror("Error: Invalid input");
		return (NULL);
	}

	/* Count the number of words in the input string */
	for (i = 0; input_str[i] != '\0'; i++)
		if ((input_str[i] != delimiter && input_str[i + 1] == delimiter) ||
		    (input_str[i] != delimiter && !input_str[i + 1]) || input_str[i + 1] == delimiter)
			num_words++;

	/* If no words are found, return NULL */
	if (num_words == 0)
	{
		perror("Error: No words found");
		return (NULL);
	}

	/* Allocate memory for the array of strings (word_array) */
	word_array = malloc((num_words + 1) * sizeof(char *));
	if (!word_array)
	{
		perror("Error: Memory allocation failed");
		return (NULL);
	}

	/* Loop to split the input string into words */
	for (i = 0, j = 0; j < num_words; j++)
	{
		/* Skip the delimiters at the beginning of each word */
		while (input_str[i] == delimiter && input_str[i] != '\0')
			i++;

		/* Calculate the length of the current word */
		k = 0;
		while (input_str[i + k] != delimiter && input_str[i + k] && input_str[i + k] != delimiter)
			k++;

		/* Allocate memory for the current word in word_array */
		word_array[j] = malloc((k + 1) * sizeof(char));
		if (!word_array[j])
		{
			/* Handle memory allocation failure */
			perror("Error: Memory allocation failed");
			/* Free previously allocated memory to avoid leaks */
			for (k = 0; k < j; k++)
				free(word_array[k]);
			free(word_array);
			return (NULL);
		}

		/* Copy the current word from the input string to word_array */
		for (m = 0; m < k; m++)
			word_array[j][m] = input_str[i++];
		word_array[j][m] = '\0';
	}

	/* Set the last element of word_array to NULL to mark the end */
	word_array[j] = NULL;

	/* Free unused memory (if any) in word_array */
	for (i = j + 1; i <= num_words; i++)
		free(word_array[i]);

	return (word_array);
}
