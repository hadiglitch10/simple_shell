#include "my_shell.h"

/**
 * unset_alias - Unsets an alias based on its name.
 * @myinfo: Pointer to the info struct containing shell information.
 * @alias: The string alias to unset.
 *
 * Return: true on success, false on error.
 */
bool unset_alias(info *myinfo, char *alias)
{
	char *equal_sign_ptr = str_char(alias, '=');
	int ret;

	if (!equal_sign_ptr)
		return (false);
	/* Invalid alias format, no equal sign */

	*equal_sign_ptr = '\0';
	/* Null-terminate alias name to extract the name part */
	ret = delete_node(&(myinfo->alias),
				get_node_index(myinfo->alias, node_starts_with(myinfo->alias, alias, -1)));
	*equal_sign_ptr = '=';
	/* Restore the original string */

	return (ret);
}

/**
 * set_alias - Sets an alias to a string.
 * @myinfo: Pointer to the info struct containing shell information.
 * @str: The string alias (e.g., "alias_name=alias_value").
 *
 * Return: 0 on success, -1 on error.
 */
int set_alias(info *myinfo, char *str)
{
	char *p = str_char(str, '=');
	char *name, *value;

	if (!p || p == str)
		return (-1);
	/* Invalid alias format, no equal sign or alias name is empty */

	*p = '\0';
	/* Null-terminate alias name to extract the name part */
	name = str;
	/* Alias name */
	value = p + 1;
	/* Alias value */

	if (!*value)
		return (unset_alias(myinfo, name));
	/* Empty alias value, remove the alias */

	if (Add_node_end(&(myinfo->alias), name, strlen(value)) == NULL)
	{
		/* Handle allocation failure */
		perror("set_alias: Memory allocation failed");
		return (-1);
	}
	return (0);
	/* Add alias to the linked list */
}

/**
 * show_alias - Prints an alias string.
 * @alias_node: The alias node containing the alias string.
 *
 * Return: true on success, false if the node is NULL or has an invalid format.
 */
bool show_alias(const list_s *alias_node)
{
	char alias_name[MAX_ALIAS_LEN + 1];
	char alias_value[MAX_ALIAS_LEN + 1];
	char *equal_sign_ptr;

	if (alias_node == NULL)
	{
		/* Error: Alias node is NULL */
		printf("show_alias: Alias node is NULL.\n");
		return (false);
	}

	equal_sign_ptr = str_char(alias_node->str, '=');

	if (equal_sign_ptr == NULL || equal_sign_ptr == alias_node->str)
	{
		/* Error: Invalid alias format or empty alias name */
		printf("show_alias: Invalid alias format or empty alias name.\n");
		return (false);
	}



	str_copy_n(alias_name, alias_node->str, equal_sign_ptr - alias_node->str);
	alias_name[equal_sign_ptr - alias_node->str] = '\0';

	str_copy_n(alias_value, equal_sign_ptr + 1, MAX_ALIAS_LEN);
	alias_value[MAX_ALIAS_LEN] = '\0';

	printf("'%s' '%s'\n", alias_name, alias_value);

	return (true);
}

/**
 * _myalias - Mimics the alias builtin (man alias).
 * @myinfo: Pointer to the info struct containing shell information.
 *
 * Return: Always 0.
 */
int _myalias(info *myinfo)
{
	int i;
	char *equal_Pos;

	if (myinfo->argc == 1)
	{
		/* No arguments provided, print all aliases */
		list_s *alias_node = myinfo->alias;

		while (alias_node)
		{
			show_alias(alias_node);
			alias_node = alias_node->nxt;
		}
	}
	else
	{
		/* Process each argument provided by the user */
		for (i = 1; i < myinfo->argc; i++)
		{
			equal_Pos = str_char(myinfo->argv[i], '=');
			if (equal_Pos)
			{
				/* Argument is an alias definition (name=value) */
				set_alias(myinfo, myinfo->argv[i]);
			}
			else
			{
				/* Argument is an alias name, print the alias */
				list_s *alias_node = node_starts_with(myinfo->alias, myinfo->argv[i], '=');

				if (alias_node)
					show_alias(alias_node);
			}
		}
	}

	return (0);
}
