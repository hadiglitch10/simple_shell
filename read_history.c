#include "my_shell.h"

/**
 * open_history_file - open the history file and get its size.
 * @filename: The filename of the history file.
 * @file_size: Pointer to store the size of the history file.
 *
 * Return: The file descriptor on success, or -1 on failure.
 */
int open_history_file(const char *filename, ssize_t *file_size)
{
	struct stat st;
	int fd = open(filename, O_RDONLY);

	if (fd == -1 || fstat(fd, &st) == -1)
	{
		perror("open_history_file: Failed to open or get file size");
		return (-1);
	}

	*file_size = st.st_size;
	return (fd);
}
/**
 * read_history_file - read the history file into a buffer.
 * @fd: The file descriptor of the history file.
 * @file_size: The size of the history file.
 * @bytes_read: Pointer to store the number of bytes read from the file.
 *
 * Return: contents of the history file, or NULL on failure.
 */
char *read_history_file(int fd, ssize_t file_size, ssize_t *bytes_read)
{
	char *buf = malloc(file_size + 1);

	if (!buf)
	{
		perror("read_history_file: malloc failed");
		return (NULL);
	}

	*bytes_read = read(fd, buf, file_size);
	buf[*bytes_read] = '\0';

	if (*bytes_read <= 0)
	{
		perror("read_history_file: read failed");
		free(buf);
		return (NULL);
	}

	return (buf);
}
/**
 * process_history_buffer - process history buffer and create entries.
 * @myinfo: Pointer to the info struct contain shell information.
 * @buf: The history buffer contents of the history file.
 * @bytes_read: The number of bytes read from the history file.
 *
 * Return: The number of history entries processed.
 */
int process_history_buffer(info *myinfo, const char *buf, ssize_t bytes_read)
{
	int i, last = 0, linecount = 0;

	for (i = 0; i < bytes_read; i++)
	{
		if (buf[i] == '\n')
		{
			char *cmd = extract_command_from_buffer(buf, last, i);

			if (cmd)
			{
				start_history_list(myinfo, cmd, linecount);
				free(cmd);
				linecount++;
			}
			else
			{
				perror("process_history_buffer: malloc failed");
				return (linecount);
			}
			last = i + 1;
		}
	}

	if (last != i)
	{
		char *cmd = extract_command_from_buffer(buf, last, i);

		if (cmd)
		{
			start_history_list(myinfo, cmd, linecount++);
			free(cmd);
			linecount++;
		}
		else
		{
			perror("process_history_buffer: malloc failed");
			return (linecount);
		}
	}
	return (linecount);
}

/**
 * extract_command_from_buffer -extract a command from the buffer.
 * @buf: The history buffer contents of the history file.
 * @start: The start index of the command in the buffer.
 * @end: The end index of the command in the buffer.
 *
 * Return: A newly string the command, or NULL on failure.
 */
char *extract_command_from_buffer(const char *buf, int start, int end)
{
	int cmd_len = end - start + 1;
	char *cmd = malloc(cmd_len + 1);

	if (cmd)
	{
		str_copy_n(cmd, buf + start, cmd_len);
		cmd[cmd_len] = '\0';
	}

	return (cmd);
}

/**
 * read_history - Reads history file.
 * @myinfo: Pointer to the info struct containing shell information.
 *
 * Return: The number of history entries read on success, 0 otherwise.
 */
int read_history(info *myinfo)
{
	char *buf = NULL;
	ssize_t bytes_read, file_size = 0;
	int linecount = 0, file_fd;
	char *filename = get_history_file(myinfo);

	if (!filename)
		return (0);
	file_fd = open_history_file(filename, &file_size);

	free(filename);
	if (file_fd == -1)
		return (0);
	buf = read_history_file(file_fd, file_size, &bytes_read);
	close(file_fd);
	if (buf == NULL || bytes_read <= 0)
	{
		free(buf);
		return (0);
	}
	linecount = process_history_buffer(myinfo, buf, bytes_read);
	free(buf);
	while (myinfo->histcnt > MAX_HISTORY_SIZE)
	{
		delete_node(&(myinfo->history), 0);
		myinfo->histcnt--;
	}
	return (linecount);
}
