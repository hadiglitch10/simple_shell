# include "my_shell.h"

/**
 * is_cmd_exec - determines if a file is an executable command
 * @myinfo: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd_exec(info *myinfo, char *path)
{
	struct stat file_stats;

	(void)myinfo;

	if (!path || stat(path, &file_stats))
	{
		/* Unable to get file stats or path is NULL */
		perror("Error in stat");
		return (0);
	}

	/* Check if the file type is a regular file */
	if ((file_stats.st_mode & __S_IFMT) == __S_IFREG)
	{
		/* It's a regular file, so it's an executable command */
		return (1);
	}

	/* Not a regular file, so it's not an executable command */
	return (0);
}

/**
 * duplicate_substring - Duplicates characters
 * @str: The source string
 * @start: Starting index of the substring
 * @end: Ending index of the substring
 *
 * Return: Pointer to a buffer
 */
char *duplicate_substring(const char *str, int start, int end)
{
	/* Check for invalid inputs */
	if (!str || start < 0 || end < 0 || end <= start)
		return (NULL);

	/* Calculate the length of the substring and allocate memory for it */
	int substring_length = end - start;
	char *substring = malloc(substring_length + 1);

	/* Check if memory allocation was successful */
	if (!substring)
	{
		perror("malloc");
		return (NULL);
	}

	/* Copy character of the source string to the new buffer */
	int i, j;

	for (i = start, j = 0; i < end; i++, j++)
	{
		substring[j] = str[i];
	}
	substring[j] = '\0'; /* Null-terminate the new substring*/
	return (substring);
}

/**
 * find_cmd_path - Finds the full path of a command in the PATH string
 * @myinfo: The info struct
 * @pathstr: The PATH string
 * @command: The command to find
 *
 * Return: A pointer to path
 */
char *find_cmd_path(info *myinfo, const char *pathstr, const char *command)
{	int i = 0, current_pos = 0;
	char *path;

	if (!pathstr || !command)
		return (NULL);
	/* Check if the command is a relative path and if it exists */
	if ((string_length(command) > 2) && begin_with(command, "./"))
	{
		if (is_cmd_exec(myinfo, command))
			return (string_dupli(command));
	}
	/* Loop through the PATH string to find the command */
	while (1)
	{
		/* Check if we reached the end of the PATH string or a ':' delimiter */
		if (!pathstr[i] || pathstr[i] == ':')
		{
			/* Extract the current path segment from the PATH string */
			path = duplicate_substring(pathstr, current_pos, i);
			if (!path)
				return (NULL);
			/* Concatenate the command to the current path segment */
			if (*path)
				string_concat(path, "/");
			string_concat(path, command);
			/* Check if the constructed path points to an executable command */
			if (is_cmd_exec(myinfo, path))
				return (path);
			/* If the command is not found, free buffer and continue searching */
			free(path);
			/* Check if we reached the end of the PATH string */
			if (!pathstr[i])
				break;
			/* Update the position in the PATH to skip the ':' */
			current_pos = i + 1;
		}
		i++;
	}
	/* If the command was not found in the PATH, return NULL */
	return (NULL);
}

/**
 * handle_cmd_found - Handles found command in PATH. Executes it.
 * @myinfo: Pointer to info struct.
 * @path: Full path of the command found.
 */

void handle_cmd_found(info *myinfo, char *path)
{
	myinfo->path = path;
	execute_cmd(myinfo);
}

/**
 * handle_cmd_not_found - Handles command not found in PATH.
 * @myinfo: Pointer to info struct.
 */

void handle_cmd_not_found(info *myinfo)
{
	if (interactive_shell(myinfo) || search_env_value(myinfo, "PATH=")
	|| myinfo->argv[0][0] == '/')

	{
		if (is_cmd_exec(myinfo, myinfo->argv[0]))
			execute_cmd(myinfo);
		else
		{
			myinfo->status = EX_UNAVAILABLE;
			perror("Command not found");
		}
	}
	else if (*(myinfo->arg) != '\n')
	{
		myinfo->status = EX_UNAVAILABLE;
		perror("Command not found");
	}
}
