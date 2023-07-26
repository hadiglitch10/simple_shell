#include "my_shell.h"

/**
 * string_cmp - a function to cpompare between two strings
 * @str1: The first string to be compared
 * @str2: The second string to be compared
 * Return: An integer less than, equal to, or greater than zero if s1 is found,
 * respectively, to be less than, to match, or be greater than s2.
 */
int string_cmp(char *str1, char *str2)
{
	while (*str1 && *str2 && (*str1 == *str2))
{
		str1++;
		str2++;
}

	if (*str1 == *str2)
		return (0);
	else if (*str1 < *str2)
	{
		return (-1);
	}
	else
	return (1);
}

/**
 * string_length - Returns the length of a string
 * @str: The string to calculate it's length
 * Return: The length of the string
 */
int string_length(char *str)
{
	int length = 0;

	if (!str)
		return (0);

	while (str[length] != '\0')
	{
		length++;
	}

	return (length);
}

/**
 * string_cpy - Copies a string from source to destination
 * @destin: The destination buffer
 * @sorc: The source string
 * Return: A pointer to the destination buffer
 */
char *string_cpy(char *destin, const char *sorc)
{
	int i = 0;
	/* make sure if the source and destination are the same or the source is NUL*/
	if (destin == sorc || sorc == NULL)
		return (destin);

	/* Copy characters from source to destination */
	for (i; sorc[i] != '\0'; i++)
	{
		destin[i] = sorc[i];
	}

	/* Add the null terminator to the destination string*/
	destin[i] = '\0';

	return (destin);
}

/**
 * str_copy_n - Copies a string with a specified number of characters.
 * @destin: The destination string to be copied to.
 * @sorc: The source string.
 * @n: The number of characters to be copied.
 *
 * Return: A pointer to the concatenated string.
 */
char *str_copy_n(char *destin, const char *sorc, int n)
{
	int i;

	/* Check if the source or destination is NULL. */
	if (sorc == NULL || destin == NULL)
	{
		perror("Error: Source or destination string is NULL");
		return (NULL);
	}

	/* Copy characters from source to destination up to the specified limit */
	for (i = 0; i < n && sorc[i] != '\0'; i++)
	{
		destin[i] = sorc[i];
	}

	/* fill with null if length is less than n*/
	for (; i < n; i++)
	{
		destin[i] = '\0';
	}

	return (destin);
}

/**
 * string_dupli - Duplicates a string
 * @str: The input string to be duplicated
 * Return: A pointer to the newly allocated duplicated string.
 * NULL if str is NULL or if memory allocation fails.
 */
char *string_dupli(const char *str)
{
	int str_len = 0;
	char *duplicate;

	/* Check if the input string is NULL*/
	if (str == NULL)
		return (NULL);

	/* Calculate the length of the input string*/
	for (; str[str_len] != '\0'; str_len++)
		;

	/* Allocate memory for the duplicate string (+1 for the null terminator)*/
	duplicate = malloc(sizeof(char) * (str_len + 1));

	/* Check if memory allocation was successful*/
	if (duplicate == NULL)
		return (NULL);

	/* Copy the characters from the input string to the duplicate string*/
	for (int i = 0; i <= str_len; i++)
		duplicate[i] = str[i];

	return (duplicate);
}
