#include "my_shell.h"

/**
 * check_chain - Checks whether to continue chaining based on last status
 * @info: The parameter struct containing command info
 * @buff: The char buffer to modify
 * @b: Address of the current position in the buffer
 * @a: Starting position in the buffer
 * @len: Length of the buffer
 * Return: nothing
 */
void check_chain(info *info, char *buff, char *b, size_t a, size_t len)
{
	size_t i = *b;

	for (; i < len; i++)
	{
		if (info == NULL || buff == NULL)
		{
			perror("Invalid parameter or memory allocation");
			exit(EXIT_FAILURE);
		}
		else if (info->cmd_type == CMD_AND_OPERATOR)
		{
			if (info->status)
			{
				buff[a] = 0;
				i = len;
			}
		}
		else if (info->cmd_type == CMD_OR_OPERATOR)
		{
			if (!info->status)
			{
				buff[a] = 0;
				i = len;
			}
		}
	}
	*b = i;
}

/**
 * chain - Check if the current character in the buffer is a chain delimiter
 * @info: A pointer to the parameter struct holding command information
 * @buff: The character buffer
 * @p: A pointer to the current position in the buffer
 * Return: 1 if it's a chain delimiter, 0 otherwise
 */
int chain(info *info, char *buff, size_t *p)
{
	size_t pos = *p;
	char current_char = buff[pos];

	switch (current_char)
	{
		case '|':
			if (buff[pos + 1] == '|')
			{
				buff[pos] = '\0';
				pos++;
				info->cmd_type = CMD_OR_OPERATOR;
			}
			break;

		case '&':
			if (buff[pos + 1] == '&')
			{
				buff[pos] = '\0';
				pos++;
				info->cmd_type = CMD_AND_OPERATOR;
			}
			break;

		case ';':
			buff[pos] = '\0';
			info->cmd_type = CMD_CHAIN_OPERATOR;
			break;

		default:
			return (0);
	}

	*p = pos;
	return (1);
}
/**
 * replace_variables - Replace variables in the tokenized string
 * @info: Pointer to the parameter struct containing info
 * Return: 1 if replaced, 0 otherwise
 */
int replace_variables(info *info) {
	int index = 0;
	list_s *node;

	while (info->argv[index]) {
		char first_char = info->argv[index][0];
		char *arg = info->argv[index];

		switch (first_char) {
			case '$':
				if (arg[1] == '?') {
					rep_str(&arg, string_dupli(convert_num(info->status, 10, 0)));
					break;
				} else if (arg[1] == '$') {
					rep_str(&arg, string_dupli(convert_num(getpid(), 10, 0)));
					break;
				}
				node = node_starts_with(info->env_list, arg + 1, '=');
				if (node) {
					rep_str(&arg, string_dupli(str_char(node->str, '=') + 1));
				} else {
					rep_str(&arg, string_dupli(""));
				}
				break;
			default:
				/* If the current argument is not starting with '$', move to the next one */
				break;
		}
		info->argv[index] = arg;
		index++;
	}
	return 0;
}

/**
 * rep_alias - Replace an alias in the tokenized string
 * @info: The parameter struct containing information
 * Return: 1 if replaced, 0 otherwise
 */
int rep_alias(info *info)
{
	int i = 0;
	list_s *node;
	char *alias_value, *temp;

	while (i < 10)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);

		free(info->argv[0]);

		alias_value = str_char(node->str, '=');
		if (!alias_value)
		{
			perror("Error: Invalid alias");
			return (0);
		}
		/* Move past the '=' character*/
		alias_value++;

		temp = string_dupli(alias_value);
		if (!temp)
		{
			perror("Error: Memory allocation failed try again");
			return (0);
		}

		info->argv[0] = temp;
		i++;
	}
	return (1);
}

/**
 * rep_str - Replaces a string with a new string
 * @old: Address of the old string
 * @new: New string
 * Return: 1 if replaced, 0 otherwise
 */
int rep_str(char **old, char *new)
{
	if (old == NULL || new == NULL)
	{
		perror("Error:  memory allocation failed or invalid input ");
		return (0);
	}

	free(*old);
	*old = new;
	return (1);
}
