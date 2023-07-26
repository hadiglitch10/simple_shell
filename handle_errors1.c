#include "my_shell.h"

/**
 * put_char_err - prints a character to the standard error stream
 * @ch: The character to be printed
 * @file_d: the file descriptor to write to
 * Return: 1 on success, -1 on failure
 */
/**
 * put_char_err - Writes a character to the file descriptor with error handling.
 * @ch: The character to be written.
 * @file_d: The file descriptor to write to.
 *
 * Return: 1 on success, -1 on failure.
 */
int put_char_err(char ch, int file_d)
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
			perror("put_char: Memory allocation failed");
			return (-1);
		}
	}

	buffer[index++] = ch;

	if (index >= BUFFER_SIZE || ch == '\n')
	{
		if (write(file_d, buffer, index) < 0) /* flush the buffered characters */
		{
			perror("put_char: Writing failed");
			free(buffer); /* deallocate memory */
			buffer = NULL;
			return (-1);
		}
		index = 0;
	}

	return (1);
}

/**
 * put_str - Prints an input string
 * @str: The string to be printed
 * Return: None
 */
void put_str_err(char *str)
{
	if (str == NULL)
	{
		perror("put_str: The input string is NULL");
		return;
	}

	for (int i = 0; str[i] != '\0'; i++)
	{
		_putchar(str[i]);
	}
}
/**
 * put_file_d - writes a character to the specified file descriptor
 * @ch: The character to be written
 * @file_d: The file descriptor to write to
 * Return: 1 on success, -1 on failure
 */
int put_char_fd(char ch, int file_d)
{
	char buf[1] = {ch};

	if (write(file_d, buf, 1) < 0)
	{
		perror("put_file_d: Write failed");
		return (-1);
	}

	return (1);
}

/**
 * custom_put - writes an input string to the specified file descriptor
 * @str: The string to be written
 * @file_d: The file descriptor to write to
 * Return: The number of characters written on success, -1 on failure
 */
int put_str_fd(char *str, int file_d)
{
	int i = 0;

	if (!str)
		return (-1);

	while (*str)
	{
		if (_putfd(*str++, file_d) < 0)/* Print the character to fd*/
		{
			/* Handle error and return -1 to indicate failure */
			perror("custom_put: Error writing to file descriptor");
			return (-1);
		}
		i++;
	}

	return (i);
}

/**
 * put_fd - writes the character c to the given file descriptor
 * @ch: The character to be written
 * @file_d: The file descriptor to write to
 * Return: On success, 1 is returned.
 * On error, -1 is returned, and errno is set appropriately.
 */
int put_char_fd(char ch, int file_d)
{
	static int i;
	static char buf[BUFFER_SIZE] = {0};

	if (ch == BUFFER_FLUSH || i >= BUFFER_SIZE)
	{
		if (write(file_d, buf, i) < 0)
		{
			perror("putfd: Write failed");
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
