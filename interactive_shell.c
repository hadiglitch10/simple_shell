#include "my_shell.h"

/**
 * find_builtin - Find a built-in command.
 * @cmd: The command entered by the user.
 *
 * Return: A pointer to the function ,
 *         or NULL if not a built-in command.
 */
int (*find_builtin(const char *cmd))(info *)
{
	int i = 0;

	while (builtintbl[i].cmd != NULL)
	{
		if (strcmp(cmd, builtintbl[i].cmd) == 0)
			return (builtintbl[i].func);
		i++;
	}

	return (NULL);
}

/**
 * execute_cmd - forks an exec thread to run cmd
 * @myinfo: the parameter & return info struct
 *
 * Return: void
 */
void execute_cmd(info *myinfo)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* Fork failed, handle the error */
		perror("Error in fork");
		return;
	}
	if (child_pid == 0)
	{
		/* Child process: execute the command */
		if (execve(myinfo->path, myinfo->argv, copy_env(myinfo)) == -1)
		{
			/* execve failed, handle the error */
			myinfo_free(myinfo, 1);
			if (errno == EACCES)
				exit(EXIT_PERMISSION_DENIED);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* Parent process: wait for the child to finish */
		wait(&(myinfo->status));
		if (WIFEXITED(myinfo->status))
		{
			myinfo->status = WEXITSTATUS(myinfo->status);
			if (myinfo->status == EXIT_PERMISSION_DENIED)
				perror("Permission denied\n");
		}
	}
}

/**
 * find_and_execute_cmd - Finds a command in PATH and executes it
 * @myinfo: The parameter & return info struct
 *
 * Return: void
 */
void find_and_execute_cmd(info *myinfo)
{
	char *cmd_path = NULL, *c = NULL;
	int num_non_delimiters = 0, i;

	if (myinfo->line_cnt_flag)
	{
		myinfo->line_cnt++;
		myinfo->line_cnt_flag = 0;
	}

	for (i = 0; myinfo->arg[i]; i++)
	{
		if (!check_delim(myinfo->arg[i], " \t\n")) /*custom*/
			num_non_delimiters++;
	}

	if (num_non_delimiters == 0)
		return;

	c = find_cmd_path(myinfo, search_env_value(myinfo, "PATH="), myinfo->argv[0]);
	cmd_path = c;

	if (cmd_path)
	{
		handle_cmd_found(myinfo, cmd_path);
		free(cmd_path);
	}
	else
	{
		handle_cmd_not_found(myinfo);
	}
}


/**
 * run_shell - Entry point for running the shell
 * @myinfo: Pointer to the info struct containing shell information
 * @argv: The argument vector from main()
 *
 * Return: 0 on success, 1 on error or error code
 */
int run_shell(info *myinfo)
{
	ssize_t read_result = 0;
	int builtin_ret = 0;
	int is_interactive = interactive_shell(myinfo);

	while (read_result != -1 && builtin_ret != -2)
	{
		null_info(myinfo);

		if (is_interactive)
			print_str("$ ");

		fflush(stdout);

		read_result = get_input(myinfo);
		if (read_result == -1)
		{
			if (is_interactive)
				put_char('\n');
			break; /* Exit loop on Ctrl+D (EOF) */
		}

		builtin_ret = find_builtin_command(myinfo);
		if (builtin_ret == -1)
			find_and_execute_cmd(myinfo);

		myinfo_free(myinfo, 0);
	}
	write_history(myinfo);
	myinfo_free(myinfo, 1);

	if (!is_interactive && myinfo->status)
		exit(myinfo->status);
	if (builtin_ret == -2)
	{
		if (myinfo->err_num == -1)
			exit(myinfo->status);
		exit(myinfo->err_num);
	}
	return (builtin_ret);
}
