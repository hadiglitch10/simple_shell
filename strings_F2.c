#include "my_shell.h"

/**
 * put_str - Prints an input string followed by a newline character
 * @str: The string to be printed
 * Return: nothing
 */
void put_str(char *str)
{
	if (!str)
		return;

	/* Use a pointer to traverse the string and print each character */
	while (*str != '\0')
	{
		_putchar(*str);
		str++;
	}
		/* Print a newline character to end the line*/
	_putchar('\n');
}

/**
 * putchar - Writes the character c to the standard output
 * @c: The character to be printed
 * Return: On success, returns 1.
 * On error, returns -1, and errno is set appropriately
 */
int putchar(char c)
{
	static int index;
	static char buff[BUFFER_SIZE];

	/* If the character is not BUF_FLUSH, store it in the buffer*/
	if (c != BUFFER_FLUSH)
	{
		buff[index++] = c;

		/* Check if the buffer is full, then flush it*/
		if (index >= BUFFER_SIZE || c == '\n')
		{
			write(1, buff, index);
			index = 0;
		}
	}

	return (1);
}

/**
 * string_concat - function to Concatenate two strin
 * @destin: The destination buffer (index) to concatenate to
 * @sorc: The source string to concatenate
 * Return: A pointer points to the beginning of the concatenated string
 */
char *string_concat(char *destin, const char *sorc)
{
	char *result = destin;

	/*Move the destination pointer to the end of the string*/
	while (*destin)
		destin++;

	/*Copy the source string to the destination*/
	while (*sorc)
	{
		*destin = *sorc;
		destin++;
		sorc++;
	}

	/*Append null terminator to the concatenated string*/
	*destin = '\0';

	return (result);
}

/**
 * begins_with - Checks if the first string begins with the second one
 * @haystack: The string to search for
 * @needle: The substring to be found
 * Return: A pointer to the next character in haystack after the needle,
 * or NULL if the substring is not found
 */
char *begins_with(const char *haystack, const char *needle)
{
		/*Loop through the needle until its end is reached*/
	for (; *needle != '\0'; haystack++, needle++)
	{
		/*Check if the characters are different.*/
		if (*needle != *haystack)
			return (NULL);
	}
	return ((char *)haystack);
}
