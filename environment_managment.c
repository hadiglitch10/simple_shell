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
	myinfo->modified_env = convert_lst2str(myinfo->env_list);

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
	variable_len = strlength(variable);
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
