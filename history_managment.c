#include "my_shell.h"


/**
 * renum_history - Renumber the history linked list after changes.
 * @myinfo: Pointer to the info struct containing shell information.
 *
 * Return: The new histcnt.
 */
int renum_history(info *myinfo)
{
	list_s *node;
	int new_histcnt = 0;

	/* Traverse the history linked list and renumber nodes */
	for (node = myinfo->history; node; node = node->nxt)
	{
		/* Assign (new_histcnt) to the current node's 'numf' field */
		node->numf = new_histcnt++;
	}

	/* Update the histcnt in the info struct with the new count */
	myinfo->histcnt = new_histcnt;

	return (new_histcnt);
}

/**
 * start_history_list - Adds an entry to a history linked list.
 * @myinfo: Pointer to the info struct containing shell information.
 * @buf: Buffer containing the command.
 * @linecount: count the length of the line
 * Return: void
 */
void start_history_list(info *myinfo, char *buf, int linecount)
{

	/* Check if invalid input or empty */
	if (myinfo == NULL || buf == NULL || *buf == '\0')
		return;

	/* Add to the end of the history list */
	Add_node_end(&(myinfo->history), buf, linecount++);
}

/**
 * get_history_file - Get the history file path.
 * @myinfo: Pointer to the info struct containing shell information.
 *
 * Return: A newly allocated string containing the history file path,
 *         or NULL on failure.
 */
char *get_history_file(info *myinfo)
{
	char *buf, *dir;
	size_t dir_len, file_len, buf_size;

	/* Get the user's home directory path */
	dir = search_env_value(myinfo, "HOME=");
	if (!dir)
		return (NULL);

	dir_len = string_length(dir);
	file_len = string_length(HISTORY_FILE);

	/* Calculate the size needed for the history file path */
	buf_size = dir_len + file_len + 2;

	/* Allocate memory for the history file path */
	buf = malloc(buf_size);
	if (!buf)
	{
		perror("get_history_file: malloc failed");
		return (NULL);
	}

	/* Construct the history file path */
	string_cpy(buf, dir);
	string_concat(buf, "/");
	string_concat(buf, HISTORY_FILE);

	return (buf);
}

/**
 * write_history - writes the history to a file.
 * @myinfo: Pointer to the info struct containing shell information.
 *
 * Return: 1 on success, -1 on failure.
 */
int write_history(info *myinfo)
{
	list_s *node;
	int fd;
	char *filename;

	if (myinfo == NULL)
		return (-1); /* Invalid info struct */

	filename = get_history_file(myinfo);

	if (filename == NULL)
		return (-1); /* Failed to get the history file path */
	fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	free(filename);
	if (fd == -1)
		return (-1); /* Failed to open the history file */
	node = myinfo->history;
	while (node != NULL)
	{
		if (put_str_fd(node->str, fd) == -1 || put_char_fd('\n', fd) == -1)
		{
			close(fd);
			return (-1);
		}
		node = node->nxt;
	}
	if (put_char_fd(BUFFER_FLUSH, fd) == -1)
	{
		/* Error occurred while flushing the buffer, close the file and return -1 */
		close(fd);
		return (-1);
	}
	/* Close the file */
	if (close(fd) == -1)
	{
		perror("write_history: close failed");
		return (-1);
	}
	return (1); /* Return 1 on success */
}
