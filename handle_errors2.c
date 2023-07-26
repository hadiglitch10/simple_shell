#include "my_shell.h"

/**
 * convert_num - converts a integer to a string
 * @num: the number to be converted
 * @base: the base for the conversion
 * @flag: argument flags for the format
 * Return: the string representation of the number if (success)
 * or NULL is returned using perror if (error)
 */
char *convert_num(long int num, int base, int flag)
{
	static char buffer[50];
	char *array, *sign;

	if (flag & CONVERT_TO_LOWERCASE)
		array = "0123456789abcdef";
	else
		array = "0123456789ABCDEF";
	/*checks for the base, minimum base (2), maximum base (16)*/
	if (base < 2 || base > 16)
	{
		perror("Error: Invalid base for conversion");
		return (NULL);
	}

	sign = (num < 0 && !(flag & CONVERT_TO_UNSIGNED)) ? '-' : '\0';
	unsigned long n = (num < 0 && !(flag & CONVERT_TO_UNSIGNED)) ? -num : num;

	char *ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;

	return (ptr);
}

/**
 * str_to_int - converts a string to an integer
 * @str: the string to be converted
 * Return: 0 if no numbers in the string, converted number otherwise
 * -1 on error (non-digit character or integer overflow)
 */
int str_to_int(char *str)
{
	int index = 0;
	unsigned long int result = 0;

	/* Check for NULL input string */
	if (str == NULL)
	{
		perror("Error: Input string is NULL");
		return (-1);
	}

	/* Handle optional leading '+' (ignore it) */
	if (*str == '+')
		str++;

	/* Convert the string to an integer */
	for (index = 0; str[index] != '\0'; index++)
	{
		/*check for positive integer*/
		if (str[index] >= '0' && str[index] <= '9')
		{
			result *= 10;
			result += (str[index] - '0');

			/* Check for integer overflow */
			if (result > INT_MAX)
			{
				perror("Error: Integer overflow");
				return (-1);
			}
		}
		else
		{
			perror("Error: Non-digit character found in the string");
			return (-1);
		}
	}

	return (result);
}

/**
 * print_decimal - prints a decimal (integer) number (base 10)
 * @num: the number to be printed
 * @file_d: the file descriptor to write to
 * Return: number of characters printed, or -1 on error.
 */
int print_decimal(int num, int file_d)
{
	int (*print_char)(char) = putchar;
	int divisor = 1000000000, count = 0;
	unsigned int abs_num, current_digit;

	if (file_d == STDERR_FILENO)
		print_char = putchar;
	abs_num = (num < 0) ? -num : num;

	if (num < 0)
	{
		if (print_char('-') == -1)
		{
			perror("Error: Failed to write to file descriptor");
			return (-1);
		}
		count++;
	}
	current_digit = abs_num;

	while (divisor > 1)
	{
		if (abs_num / divisor)
		{
			if (print_char('0' + current_digit / divisor) == -1)
			{
				perror("Error: Failed to write to file descriptor");
				return (-1);
			}
			count++;
		}
		current_digit %= divisor;
		divisor /= 10;
	}
	if (print_char('0' + current_digit) == -1)
	{
		perror("Error: Failed to write to file descriptor");
		return (-1);
	}
	count++;
	return (count);
}
/**
 * remove_comments - Removes the comment from a string buffer
 * @input_buff: Pointer to the input buffer
 */
void remove_comments(char *input_buff)
{
	int i = 0;

	if (input_buff == NULL)
	{
		perror("Error: Input buffer is NULL.");
		return;
	}

	while (input_buff[i] != '\0')
	{
		if (input_buff[i] == '#' && (i == 0 || input_buff[i - 1] == ' '))
		{
			input_buff[i] = '\0';
			break;
		}
		i++;
	}
}


/**
 * print_error - Prints an error message.
 * @info: Pointer to the info struct containing file and line information.
 * @str_err: String containing the specified error type.
 */
void print_error(info *info, char *str_err)
{
	if (info == NULL || str_err == NULL)
	{
		perror("Error: Invalid arguments.");
		return;
	}

	if (info->fname != NULL)
	{
		fprintf(stderr, "%s: ", info->fname);
	}

	fprintf(stderr, "%d: ", info->line_cnt);

	if (info->argv != NULL && info->argv[0] != NULL)
	{
		fprintf(stderr, "%s: ", info->argv[0]);
	}

	fprintf(stderr, "%s\n", str_err);
}
