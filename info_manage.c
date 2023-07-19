#include "my_shell.h"

/**
 * null_info - Initialize the struct
 * @myinfo: The struct to clear
 */
void null_info(info *myinfo)
{
	/* Reset the dynamically allocated fields to NULL */
	free(myinfo->arg);
	free(myinfo->argv);
	free(myinfo->path);

	/* Reset other fields to their initial values or NULL */
	myinfo->arg = NULL;
	myinfo->argv = NULL;
	myinfo->path = NULL;
	myinfo->argc = 0;
}

/**
 * create_argv_manually - Create argv with one element or NULL if arg is NULL
 * @myinfo: Struct dealing with
 * @arg: Argument to clone or NULL
 *
 * Return: Array of arguments or NULL on failure
 */
char **create_argv_manually(info *myinfo, char *arg)
{
	/* Free any previously allocated memory for myinfo->argv*/
	if (myinfo->argv)
	{
		free(myinfo->argv);
		myinfo->argv = NULL;
	}

	/*allocate memory for myinfo->argv*/
	myinfo->argv = malloc(sizeof(char *) * 2);
	if (!myinfo->argv)
	{
		perror("malloc");
		return (NULL);
	}

	/* Set the first element of myinfo->argv*/
	if (arg)
	{
		myinfo->argv[0] = str_duplicate(arg);
		if (!myinfo->argv[0])
		{
			free(myinfo->argv); /* Free allocated memory on failure*/
			myinfo->argv = NULL;
			return (NULL);
		}
	}
	else
	{
		myinfo->argv[0] = NULL;
	}

	myinfo->argv[1] = NULL;

	return (myinfo->argv);
}


/**
 * initialize_info - Set the info passed
 * @myinfo: Args
 * @argv: Array of args
 */
void initialize_info(info *myinfo, char **argv)
{
	int argcnt;

	if (myinfo->arg != NULL)
	{
		myinfo->argv = split_str(myinfo->arg, "\t");

		for (argcnt = 0; myinfo->argv[argcnt] != NULL; argcnt++)
			;

		myinfo->argc = argcnt;
	}
	else
	{
		myinfo->argv = create_argv_manually(myinfo, NULL);

		for (argcnt = 0; myinfo->argv[argcnt] != NULL; argcnt++)
			;

		myinfo->argc = argcnt;
	}

	/* Alias and variable replacements here if needed */
}

/**
 * myinfo_free - free the struct manually
 *
 * @myinfo: the struct
 * @freeall: permision to free all
 *
*/

void myinfo_free(info *myinfo, int freeall)
{
	arr_free(myinfo->argv);
	myinfo->path = NULL;
	myinfo->argv = NULL;

	if (freeall == 1)
	{
		arr_free(myinfo->env_modify);
		myinfo->modified_env = NULL;
		blocks_free((void **)&myinfo->cmd_buffer);

		if (!myinfo->cmd_buffer)
			free(myinfo->arg);
		else if (myinfo->env_list)
			empty_list(&(myinfo->modified_env));
		else if (myinfo->history)
			empty_list(&(myinfo->history));
		else if (myinfo->alias)
			empty_list(&(myinfo->alias));
		else if (myinfo->rdfd > 2)
		{
			close(myinfo->rdfd);
		}

		fflush(stdout);

		/*dont forget empty list arr blocks*/
	}
}
