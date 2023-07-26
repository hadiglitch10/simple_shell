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
	myinfo->argc = 0;
	myinfo->arg = NULL;
	myinfo->argv = NULL;
	myinfo->path = NULL;
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
		myinfo->argv[0] = string_dupli(arg); /*boudy*/
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
void initialize_info(info *myinfo)
{
	int argcnt;

	if (myinfo->arg != NULL)
	{
		myinfo->argv = split_str_to_words(myinfo->arg, '\t'); /*boudy splitstr*/
		myinfo->argv = split_str_to_words(myinfo->arg, '\t'); /* Use '\t' as the delimiter */

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
	funfree(myinfo->argv); /* custom */
	funfree(myinfo->argv); /* custom */
	myinfo->path = NULL;
	myinfo->argv = NULL;

	if (freeall == 1)
	{
		if (!myinfo->cmd_buffer)
			free(myinfo->arg);
		else if (myinfo->env_list)
			free_link_list(&(myinfo->env_list));
		else if (myinfo->history)
			free_link_list(&(myinfo->history));
		else if (myinfo->alias)
			free_link_list(&(myinfo->alias));
		else if (myinfo->rdfd > 2)
		{
			close(myinfo->rdfd);
		}

		fflush(stdout);
	}
}
