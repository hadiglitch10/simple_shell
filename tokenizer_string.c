#include "my_shell.h"
/**
 * count_words - Counts the numbr of words in a string
 * @str: The input string
 * @delimiter: The delimiter character
 * Return: The number of words in the string
 */
int count_words(const char *str, char delimiter)
{
	if (str == NULL || *str == '\0')
	{
		perror("Error: Input string is NULL or empty");
		return (0);
	}

	int i = 0, num_words = 0;

	while (str[i] != '\0')
	{
		if ((str[i] != delimiter && str[i + 1] == delimiter) ||
			(str[i] != delimiter && str[i + 1] == '\0') || str[i + 1] == delimiter)
			num_words++;
		i++;
	}

	return (num_words);
}
/**
 * allocate_memo - Allocates memory for an array of strings
 * @num_words: The number of words in the array
 * Return: A pointer to the allocated memory or NULL on failure
 */
char **allocate_memo(int num_words)
{
	char **words = malloc((1 + num_words) * sizeof(char *));

	if (!words)
	{
		perror("Error: Memory allocation failed");
		return (NULL);
	}
	return (words);
}
/**
 * extract_word - Extracts a word from the input string
 * @str: The input string
 * @i: The current index in the string
 * @delimiter: The delimiter character
 * Return: The length of the extracted word
 */
int extract_word(const char *str, int i, char delimiter)
{
	int word_len = 0;

	while (str[i + word_len] != delimiter
	&& str[i + word_len] && str[i + word_len] != delimiter)
		word_len++;
	return (word_len);
}

/**
 * split_str_to_words - Splits a string into words
 * @str: The input string
 * @delimiter: The delimiter character
 * Return: A pointer to an array of strings, or NULL on failure
 */
char **split_str_to_words(const char *str, char delimiter)
{
	int num_words = count_words(str, delimiter);

	if (num_words == 0)
		return (NULL);

	char **words = malloc((num_words + 1) * sizeof(char *));

	if (!words)
		return (NULL);

	int i = 0, j = 0;

	while (j < num_words)
	{
		while (str[i] == delimiter)
			i++;
		int word_len = extract_word(str, i, delimiter);

		words[j] = malloc((word_len + 1) * sizeof(char));
		if (!words[j])
		{
			perror("Error: Memory allocation failed");
			while (j > 0)
				free(words[--j]);
			free(words);
			return (NULL);
		}
		int m = 0;

		while (m < word_len)
		{
			words[j][m] = str[i];
			i++;
			m++;
		}
		words[j][m] = '\0';
		j++;
	}
	words[j] = NULL;
	return (words);
}
