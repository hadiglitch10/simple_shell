#include "my_shell.h"

/**
 * check_alpha - checks for alphabetic character
 * @character: The character to check
 * Return: 1 if c is alphabetic, 0 otherwise, -1 on error
 */
int check_alpha(int character)
{
	if ((character >= 'a' && character <= 'z') ||
	(character >= 'A' && character <= 'Z'))
		return (1);
	else if (character >= 0 && character <= 127)
	/* ASCII range check for alphabetic*/
	{
		fprintf(stderr, "check_alpha: Not an alphabetic character: %c\n", character);
		return (0);
	}
	else
	{
		perror("_isalpha: Invalid character");
		return (-1);
	}
}
/**
 * check_delim - checks if character is a delimiter
 * @character: the char to check
 * @delim: the delimiter string
 * Return: 1 if true, 0 if false, -1 on error
 */
int check_delim(char character, char *delim)
{
	if (delim == NULL)
	{
		perror("check_delim: Delimiter string is NULL");
		return (-1);
	}

	for (; *delim; delim++)
	{
		if (*delim == character)
			return (1);
	}

	return (0);
}
/**
 * interactive_shell - returns true if shell is in interactive mode
 * @info: struct address
 * Return: 1 if interactive mode, 0 otherwise, -1 on error
 */
int interactive_shell(info *info)
{
	if (info == NULL)
	{
		perror("interactive_shell: Invalid 'info' pointer");
		return (-1);
	}

	if (!isatty(STDIN_FILENO))
	{
		fprintf(stderr, "interactive_shell: Standard input is not a terminal\n");
		return (0);
	}

	if (info->rdfd > 2)
	{
		fprintf(stderr, "interactive_shell: 'rdfd' should be 2 or less\n");
		return (0);
	}

	return (1);
}
/**
 * str_char - Locates a character in a string.
 * @str: The string to be searched.
 * @target: The character to look for.
 * Return: A pointer to the first occurrence of the character,
 *         or NULL if the character is not found.
 */
char *str_char(char *str, char target)
{
	while (*str != '\0')
	{
		if (*str == target)
			return (str);
		str++;
	}

	/* Check if 'target' is the null terminator */
	if (target == '\0')
		return (str);

	return (NULL);
}
