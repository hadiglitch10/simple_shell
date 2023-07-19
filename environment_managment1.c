#include "my_shell.h"

/**
 * new_env - make new env
 *
 * @myinfo: struct
 *
 * Return: 0 on success , 1 on failure
*/

int new_env(info *myinfo)
{

	if (myinfo->argc != 3)
	{
		perror("3 arguments needed");
		return (1);
	}
	else
	{
		if (env_new_app(myinfo, myinfo->argv[1], myinfo->argv[2]) == 1)
		{
			return (0);
		}
		else
		{
			return (1);
		}

	}
}

/**
 * share_env_list - share env linked list
 * @myinfo: Structure
 * Return: 0 on success, 1 on failure
 */
int share_env_list(info *myinfo)
{
	list_s *head = NULL;
	size_t i = 0;

	while (environ[i])
	{
		if (add_node_end(&head, environ[i], 0) == NULL)
		{
			perror("Error adding node to the linked list");
			free_list(head);
			/*Free list if there's allocation error*/
			return (1);
		}
		i++;
	}

	myinfo->env_list = head;
	return (0);
}

#include <stdio.h>
#include <stdlib.h>
#include "my_shell.h"

/**
 * my_unsetenv - Remove an environment variable
 * @myinfo: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int my_unsetenv(info *myinfo)
{
	int i = 1;

	/*we need 2 args at least*/
	if (myinfo->argc == 1)
	{
		perror("Too few arguments.\n");
		return (1);
	}

	/*remove the desired env*/
	for (; i < myinfo->argc; i++)
	{
		if (!remove_env(myinfo, myinfo->argv[i]))
		{
			perror("Variable not found.\n");
			return (1);
		}
	}

	return (0);
}
