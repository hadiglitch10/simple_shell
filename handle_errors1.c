#include "my_shell.h"

/**
 * put_char_fd - Writes a character to the file descriptor with error handling.
 * @ch: The character to be written.
 * @file_d: The file descriptor to write to.
 *
 * Return: 1 on success, -1 on failure.
 */
int put_char_fd(char ch, int file_d)
{
	static char *buffer;
	static int index;

	if (ch == EOF) /* Ignore EOF character (end-of-file = -1) */
		return (1);

	if (buffer == NULL)
	{
		buffer = malloc(BUFFER_SIZE);
		if (buffer == NULL)
		{
			perror("put_char_fd: Memory allocation failed");
			return (-1);
		}
	}

	buffer[index++] = ch;

	if (index >= BUFFER_SIZE || ch == '\n')
	{
		if (write(file_d, buffer, index) < 0) /* flush the buffered characters */
		{
			perror("put_char_fd: Writing failed");
			free(buffer); /* deallocate memory */
			buffer = NULL;
			return (-1);
		}
		index = 0;
	}

	return (1);
}

/**
 * put_str_err - Prints an input string.
 * @str: The string to be printed.
 *
 * Return: None.
 */
void put_str_err(const char *str)
{
	int i = 0;
	if (str == NULL)
	{
		perror("put_str_err: The input string is NULL");
		return;
	}

	for (i = 0; str[i] != '\0'; i++) /* Initialize 'i' with 0*/
	{
		put_char_fd(str[i], 2); /* Print the character to standard error (fd 2) */
	}
}

/**
 * put_str_fd - Writes an input string to the specified file descriptor.
 * @str: The string to be written.
 * @file_d: The file descriptor to write to.
 *
 * Return: The number of characters written on success, -1 on failure.
 */
int put_str_fd(char *str, int file_d)
{
	int i = 0;
	if (!str)
		return (-1);

	while (str[i])
	{
		if (put_char_fd(str[i], file_d) < 0) /* Print char to the given fd */
		{
			/* Handle error and return -1 to indicate failure */
			perror("put_str_fd: Error writing to file descriptor");
			return (-1);
		}
		i++;
	}

	return (i);
}

/**
 * put_char_err - Writes the character c to the given file descriptor.
 * @ch: The character to be written.
 *
 * Return: On success, 1 is returned.
 * On error, -1 is returned, and errno is set appropriately.
 */
int put_char_err(char ch)
{
	static int i;
	static char buf[BUFFER_SIZE] = {0};

	if (ch == BUFFER_FLUSH || i >= BUFFER_SIZE)
	{
		if (write(2, buf, i) < 0)
		{
			perror("put_char_err: Write failed");
			return (-1);
		}
		i = 0;
	}

	if (ch != BUFFER_FLUSH)
	{
		buf[i++] = ch;
	}

	return (1);
}
