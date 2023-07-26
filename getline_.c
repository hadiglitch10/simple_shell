#include "my_shell.h"

/**
 * control_c - Signal handler for SIGINT (Ctrl+C).
 * @sig_num: The signal number (unused).
 *
 * Return: void
 */
void control_c(int sig_num)
{
	/* Avoid unused parameter warning */
	(void)sig_num;

	/* New line after Ctrl+C */
	_puts("\n");

	/* Print the shell prompt */
	_puts("$ ");

	/* Flush the output buffer */
	_fflush(stdout);

	/*
	 * Handle any ongoing background processes here
	 * if applicable.
	 */

	/*
	 * Perform cleanup or specific tasks on SIGINT
	 * if needed.
	 *
	 * Note: Avoid extensive operations in a signal handler.
	 */

	/* Program execution continues after the handler */

	/*
	 * Alternatively, you can use signal(SIGINT, SIG_DFL);
	 * to restore default behavior and terminate on Ctrl+C.
	 */
}

/**
 * read_buffer - Reads data into a buffer from a file descriptor.
 * @myinfo: Pointer to the info struct containing relevant information.
 * @buf: Buffer to store the read data.
 * @bytes_read: Pointer to store the number of bytes read.
 *
 * Return: On success, the number of bytes read. On failure to read,
 * it returns 0.
 */
ssize_t read_buffer(info *myinfo, char *buf, size_t *bytes_read)
{
	/* If bytes_read is already more 0, reset indicate no data was read. */
	if (*bytes_read > 0)
	{
		*bytes_read = 0;
		return (0);
	}

	/* Attempt to read data from the file descriptor into the buffer. */
	ssize_t bytes_read_now = read(myinfo->rdfd, buf, BUFFER_SIZE);

	/* read successfully, update value of bytes_read */
	if (bytes_read_now > 0)
		*bytes_read = bytes_read_now;

	/*number of bytes read on success, or 0 on failure to read. */
	return (bytes_read_now);
}

/**
 * input_buf - Buffers chained commands.
 * @myinfo: Pointer to the parameter struct containing relevant information.
 * @buf: Address of the buffer (pointer to char pointer).
 * @len: Address of the len variable (size_t pointer).
 *
 * Return: The number of bytes read, or -1 on failure.
 */
ssize_t input_buf(info *myinfo, char **buf, size_t *len)
{
	if (*len == 0)
	{
		/* Buffer is empty, read new input from stdin */
		/* Free the previous buffer */
		free(*buf);
		*buf = NULL;
		/* Set the signal handler for SIGINT (Ctrl-C) */
		signal(SIGINT, control_c);

		ssize_t r = _getline(myinfo, buf, len);

		if (r == -1)
		{
			perror("input_buf: getline failed");
			return (-1);
		}
		if (r == 0)
			return (0); /* End of input reached */

		/* Check input ends with a newline to remove it */
		if ((*buf)[r - 1] == '\n')
		{
			(*buf)[r - 1] = '\0';
			r--;
		}
		/* indicate that a new command has been read */
		myinfo->line_cnt_flag = 1;
		/* Remove comments from the input buffer */
		remove_comments(*buf);
		/* Build history list with the command and increment histcount */
		start_history_list(myinfo, *buf, myinfo->histcnt++);
		/* Update len with the number of bytes read */
		*len = r;
		/* Set cmd_buf in info to point to the buffer */
		myinfo->cmd_buffer = buf;
	}
	/* Return the number of bytes read */
	return (*len);
}

/**
 * get_input - gets a line minus the newline
 * @myinfo: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info *myinfo)
{
	static char *buf;
	static size_t i, len;
	ssize_t r = 0;
	char **buf_p = &(myinfo->arg), *p;
	static size_t cmd_start_index;
	/*Static variable to keep track of the command's starting index*/

	_putchar(BUFFER_FLUSH);
	r = input_buf(myinfo, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		p = buf + cmd_start_index;
		/*Use cmd_start_index to get the start of the command*/
		check_chain(myinfo, buf, p, &i, len);
		/*check_chain is implemented and modifies the value of 'i'*/
		/*Loop to find the end of the command*/
		while (i < len)
		{
			if (chain(myinfo, buf, &i))
				break;
			i++;
		}
		cmd_start_index = i + 1;
		/*Update the cmd_start_index for the next call*/
		if (i >= len)
		{
			cmd_start_index = i = len = 0;
		/*Reset the cmd_start_index and other variables for the next input*/
			myinfo->cmd_type = CMD_NORMAL;
		}
		*buf_p = p;
		return (i - (p - buf));
		/*Return the number of bytes read from the buffer*/
	}
	*buf_p = buf;
	return (r);
}

/**
 * my_get_next_line - Read the next line of input from STDIN
 * @myinfo: Pointer to the info struct containing relevant information.
 * @buffer: Address of pointer to buffer, preallocated or NULL.
 * @size: Size of preallocated buffer if not NULL.
 *
 * Return: The length of the line read, or -1 on failure.
 */
int my_get_next_line(info *myinfo, char **buffer, size_t *size)
{
	static char read_buf[BUFFER_SIZE];
	static size_t read_idx, read_len;
	ssize_t read_result;
	size_t newline_idx, line_len = 0;
	char *current_buf = *buffer, *new_buf = NULL, *newline_ptr;

	if (!current_buf || !size)
		line_len = 0;
	else
		line_len = *size;
	if (read_idx == read_len)
	{
		read_idx = 0;
		read_result = read_buffer(myinfo, read_buf, &read_len);
		if (read_result == -1 || (read_result == 0 && read_len == 0))
			goto free_buffer;

		if (read_len == 0)
			return (-1);
	}
	newline_ptr = strchr(read_buf + read_idx, '\n');
	newline_idx = newline_ptr ? 1 + (size_t)(newline_ptr - read_buf) : read_len;
	new_buf = reallocate(current_buf, line_len, line_len + newline_idx + 1);
	if (!new_buf)
		goto free_buffer;

	str_concat_n(new_buf, read_buf + read_idx, newline_idx);
	line_len += newline_idx;
	read_idx += newline_idx;
	if (newline_ptr)
	{
		*buffer = new_buf;
		*size = line_len;
		return (line_len);
	}
free_buffer:
	free(new_buf);
	*buffer = NULL;
	*size = 0;
	return (-1);
}
