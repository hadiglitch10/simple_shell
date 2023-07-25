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
		_puts(*line++);
		_putchar('\n');
	}

	return (0);
}

/**
 * str_to_int - Convert a string to an integer.
 * @str: The string to convert.
 *
 * Return: The integer representation of the string, or -1 on error.
 */
int str_to_int(const char *str)
{
	int result = 0;
	int i = 0;
	bool is_negative = false;

	/* Handle the negative sign if present */
	if (str[0] == '-')
	{
		is_negative = true;
		i = 1;
	}

	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			result = result * 10 + (str[i] - '0');
			i++;
		}
		else
		{
		/* Invalid character in the string, return -1 to indicate an error. */
			return (-1);
		}
	}

	return (is_negative ? -result : result);
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
			_eputs(myinfo->argv[1]);
			_eputchar('\n');
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
	{	target_directory = _getenv(myinfo, "HOME=");
		if (!target_directory)
		{	target_directory = _getenv(myinfo, "PWD=");
			if (!target_directory)
				target_directory = "/";
		}
		chdir_result = chdir(target_directory);
	}
	else if (_strcmp(myinfo->argv[1], "-") == 0)
	{	/* If the argument is "-", go to the previous directory (OLDPWD) */
		target_directory = _getenv(myinfo, "OLDPWD=");
		if (!target_directory)
		{
			_puts(current_directory);
			_putchar('\n');
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
	_setenv(myinfo, "OLDPWD", current_directory);
	_setenv(myinfo, "PWD", getcwd(buffer, 1024));

	return (0);
}
