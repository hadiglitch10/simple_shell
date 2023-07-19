#include "my_shell.h"

/**
 * copy_env - it make a copy from the passed env
 *
 * @myinfo: struct for env
 *
 * Return: the copied env
*/

char **copy_env(info *myinfo)
{
	/*check if our copy is null or there is change*/
	if (myinfo->modified_env == NULL || myinfo->env_modify == 1)
	{

	/*change the linked to str to cpy it in array*/
	myinfo->modified_env = convert_lst2str(myinfo->env_list); /*custom*/

		if (myinfo->modified_env == NULL)
		{
			perror("Error converting environment to array");
			exit(EXIT_FAILURE);
		}

	/*indicate there is no changesss*/
	myinfo->env_modify = 0;

	}
	else
	{
		perror("there are no changes or new env");
	}
	/*return the copied version*/
	return (myinfo->modified_env);
}

/**
 * env_new_app - Add or modify an environment variable
 * @myinfo: Structure
 * @variable: environment variable property
 * @value: the environment variable value
 *
 * Return: 0 on success, 1 on failure
 */
int env_new_app(info *myinfo, char *variable, char *value)
{	/*declare the variables*/
	char *env_str = NULL;
	list_s *node;
	char *variable_match;
	size_t variable_len, value_len;

	/*check if the variables contain nothing*/
	if (!variable || !value)
		return (1);
	/*getting the length of passed args to check*/
	variable_len = strlength(variable); /*custom*/
	value_len = strlength(value);
	/*alloocate memo for var to contain them*/
	env_str = malloc(variable_len + value_len + 2);
	/*memo error handling*/
	if (!env_str)
	{
		perror("malloc");
		return (1);
	}
	/*make the variable*/
	_strcpy(env_str, variable);
	env_str[variable_len] = '=';
	_strcpy(env_str + variable_len + 1, value);
	env_str[variable_len + value_len + 1] = '\0';
	/*ckeck if there is old one to modify*/
	for (node = myinfo->env_list; node; node = node->nxt)
	{variable_match = first_str(node->str, variable);

		if (variable_match && *variable_match == '=')
		{	/*point to the new one*/
			free(node->str);
			node->str = env_str;
			myinfo->env_modify = 1;
			return (0);
		}
	}
	/*add the modifications to the list*/
	add_node_end(&(myinfo->env_list), env_str, 0);
	myinfo->env_modify = 1;
	return (0);
}

/**
 * remove_env - Remove an environment variable from the list
 * @myinfo: Structure contain arguments and env var
 * Return: 1 on success, 0 variable not found or
 *         was an error
 * @var_2be_removed: The name of the environment variable to remove
 */
int remove_env(info *myinfo, char *var_2be_removed)
{
	list_s *prev = NULL;
	list_s *current = myinfo->env_list;

	if (!myinfo->env_list || !var_2be_removed)
		return (0);

	for (current; current; prev = current, current = current->nxt)
	{
		char *variable_match = first_str(current->str, var_2be_removed);

		if (variable_match && *variable_match == '=')
		{
			if (prev)
				prev->nxt = current->nxt;
			else
				myinfo->env_list = current->nxt;

			free(current->str);
			free(current);
			myinfo->env_modify = 1;
			return (1); /* Variable found and removed*/
		}
	}

	return (0); /*Variable not found*/
}

/**
 * current_env - prints the current environment
 * @myinfo: Structure Used to maintain
 * constant function prototype
 * Return: Always 0
 */
int current_env(info *myinfo)
{
	/*check if passed env is true*/
	if (!myinfo || !(myinfo->env_list))
	{
		perror("Invalid info or environment list is empty");
		return (1);
	}

	/*point to the first element*/
	list_s *node = myinfo->env_list;
	size_t env_cnt = 0;

	/*iterate through the list*/
	while (node)
	{
		/*print if there is element*/
		if (node->str)
			_puts(node->str);

		/*print nill if empty*/
		else
			_puts("(nil)"); /*custom*/

		/*end the line*/
		_puts("\n");

		/*point to the next node to print*/
		node = node->nxt;

		/*count num of printed element*/
		env_cnt++;
	}

	return (0);
}

/**
 * search_env_value - search value of wanted env
 * @myinfo: Structure Used to maintain
 * @wanted_var: The name of the environment variable
 * Return: value wanted env, or NULL if not found
 */
char *search_env_value(info *myinfo, const char *wanted_var)
{
	list_s *current_node = myinfo->env_list;
	char *curr_value;

	while (current_node)
	{
		curr_value = current_node->str;

		while (*wanted_var && *curr_value == *wanted_var)
		{
			wanted_var++;
			curr_value++;
		}

		if (*wanted_var == '\0' && *curr_value == '=')
			return (curr_value + 1);
		 /*Return the value part of the environment variable*/

		wanted_var -= (curr_value - current_node->str) + 1;
		/*Reset name pointer*/
		current_node = current_node->nxt;
	}

	return (NULL); /*Variable not found*/
}
