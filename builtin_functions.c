#include "my_shell.h"

/**
 * builtin_help - Display help information about the built-in commands.
 * @myinfo: Pointer to the info struct containing shell information.
 *
 * Return: Always 0.
 */
int builtin_help(info *myinfo)
{
	static const char *const help_message[] = {
		"Shell Help",
		"Usage: command [arguments]\n",
		"List of built-in commands:",
		"  help        Display help information about the built-in commands.",
		"  exit        Exit the shell.",
		"  env         Display the environment variables.",
		"  history     Display the command history.",
		"  setenv      Set or update an environment variable.",
		"  unsetenv    Remove an environment variable.",
		"  cd          Change the current directory.",
		"  alias       Create an alias for a command.",
		NULL
	};

	const char *const *line = help_message;

	while (*line)
	{
		put_str(*line++);
		put_char('\n');
	}

	return (0);
}

/**
 * builtin_exit - Exits the shell with a given exit status or error code.
 * @myinfo: Pointer to the info struct containing shell information.
 *
 * Return: Always returns -2 to indicate an exit with a status or error code.
 */
int builtin_exit(info *myinfo)
{
	if (myinfo->argv[1]) /* If there is an exit argument */
	{
		int exit_status = str_to_int(myinfo->argv[1]);

		if (exit_status == -1)
		{
			myinfo->status = 2;
			perror("Illegal number");
			put_str_err(myinfo->argv[1]);
			put_char_err('\n');
			return (1); /* Return non-zero to indicate an error */
		}

		myinfo->err_num = exit_status;
		return (-2);
	}

	myinfo->err_num = -1;
	return (-2);
}

/**
 * _cd - Changes the current directory of the process.
 * @myinfo: Pointer to the info struct containing shell information.
 *
 * Return: Always 0.
 */
int _cd(info *myinfo)
{	char *current_directory, *target_directory, buffer[1024];
	int chdir_result;

	current_directory = getcwd(buffer, 1024);
	if (!current_directory)
	{	perror("getcwd");
		return (1);
	}
	if (!myinfo->argv[1])
	{	target_directory = search_env_value(myinfo, "HOME=");
		if (!target_directory)
		{	target_directory = search_env_value(myinfo, "PWD=");
			if (!target_directory)
				target_directory = "/";
		}
		chdir_result = chdir(target_directory);
	}
	else if (string_cmp(myinfo->argv[1], "-") == 0)
	{	/* If the argument is "-", go to the previous directory (OLDPWD) */
		target_directory = search_env_value(myinfo, "OLDPWD=");
		if (!target_directory)
		{
			put_str(current_directory);
			put_char('\n');
			return (1);
		}
		chdir_result = chdir(target_directory);
	}
	else
	{	/* Change to the specified directory (argument) */
		chdir_result = chdir(myinfo->argv[1]);
	}
	if (chdir_result == -1)
	{	/* If chdir returns -1, there was an error changing directory */
		perror("chdir");
		return (1);
	}
	env_new_app(myinfo, "OLDPWD", current_directory);
	env_new_app(myinfo, "PWD", getcwd(buffer, 1024));

	return (0);
}
