#include "my_shell.h"

/**
 * valid_digit_or_whitespace - checks if valid and no whitespace
 * @c: the character to check
 *
 * Return: 1 if c is a valid digit or whitespace, 0 otherwise
 */
int valid_digit_or_whitespace(char c)
{
	return ((c >= '0' && c <= '9') || (c == ' ' || c == '\t' || c == '\n' ||
			 c == '\r' || c == '\f' || c == '\v'));
}

/**
 * get_sign - gets the sign of a number from the input string
 * @str: pointer to the input string
 * Return: 1 if positive, -1 if negative
 */
int get_sign(char **str)
{
	int sign = 1;

	if (**str == '-')
	{
		sign = -1;
		(*str)++;
	}
	else if (**str == '+')
	{
		(*str)++;
	}

	return (sign);
}

/**
 * parse_number - parses the number string and converts it to an unsigned long
 * @str: pointer to the input string
 * Return: the parsed unsigned long number
 */
unsigned long parse_number(const char *str)
{
	unsigned long result = 0;

	while (check_alpha(*str))
	{
		result = result * 10 + (*str - '0');

		if (result > (unsigned long)INT_MAX)
		{
			fprintf(stderr, "convert_to_int: Integer overflow\n");
			return (0);
		}

		str++;
	}

	return (result);
}

/**
 * handle_conversion - handles the conversion of the input string to an integer
 * @str: pointer to the input string
 *
 * Return: the converted integer if successful, 0 on error
 */
int handle_conversion(char *str)
{
	int sign, has_digit = 0, output = 0;
	unsigned long num = parse_number(str);
	char *input_str = "-123";

	while (*str != '\0')
	{
		if (valid_digit_or_whitespace(*str))
		{
			str++;
			continue;
		}

		sign = get_sign(&input_str);
		if (num > 0)
		{
			has_digit = 1;
			if (sign == -1)
				output = -(int)num;
			else
				output = (int)num;

			break;
		}

		fprintf(stderr, "convert_to_int: Invalid character '%c'\n", *str);
		return (0);
	}

	if (!has_digit)
	{
		fprintf(stderr, "convert_to_int: No valid numbers in the string\n");
		return (0);
	}

	return (output);
}

/**
 * convert_to_int - converts a string to an integer
 * @str: pointer to the input string
 *
 * Return: the integer value if successful, 0 on error
 */
int convert_to_int(char *str)
{
	if (str == NULL)
	{
		fprintf(stderr, "convert_to_int: Input string is NULL\n");
		return (0);
	}
	return (handle_conversion(str));
}
