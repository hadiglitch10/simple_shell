#include "my_shell.h"
/**
 * string_concat - Concatenate two strings
 * @dest: The destination buffer to concatenate to
 * @src: The source string to concatenate
 * Return: A pointer to the destination string
 */
char *string_concat(char *dest, const char *src)
{
	char *result = dest;

	/*Move the destination pointer to the end of the string*/
	while (*dest)
		dest++;

	/*Copy the source string to the destination*/
	while (*src)
	{
		*dest = *src;
		dest++;
		src++;
	}

	/*Append null terminator to the concatenated string*/
	*dest = '\0';

	return (result);
}
/**
 * begin_with - Checks if the first string begins witj the second one
 * @haystack: The string to search for
 * @needle: The substring to be found
 * Return: A pointer to the next character in haystack after needle,
 *         or NULL if the substring is not found
 */
char *begin_with(const char *haystack, const char *needle)
{
	/* Loop through the needle until its end is reached*/
	for (; *needle != '\0'; haystack++, needle++)
	{
		/* Check if the characters are different*/
		if (*needle != *haystack)
			return (NULL);
	}

	/* Return the pointer to the next character in haystack after needle*/
	return ((char *)haystack);
}

/**
 * put_char - Writes the character c to the standard output (stdout)
 * @c: The character to print
 * Return: On success, returns 1
 * On error, returns -1, and errno is set appropriately.
 */
int put_char(char c)
{
	static int index;
	static char write_buffer[BUFFER_SIZE];

	/* If the character is not BUF_FLUSH, store it in the buffer*/
	if (c != BUFFER_FLUSH)
	{
		write_buffer[index++] = c;

		/* Check if the buffer is full, then flush it*/
		if (index >= BUFFER_SIZE || c == '\n')
		{
			write(1, write_buffer, index);
			index = 0;
		}
	}

	return (1);
}
/**
 * print_str - Prints an input string in reverse order
 * @input_string: The string to be printed
 * Return: Nothing
 */
void print_str(char *input_string)
{
	if (!input_string)
	{
		perror("custom_puts error: Input string is NULL");
		return;
	}

	size_t str_length = strlen(input_string);

	printf("Reversed string: ");
	for (int i = str_length - 1; i >= 0; i--)
	{
		putchar(input_string[i]);
	}

	putchar('\n');
}
