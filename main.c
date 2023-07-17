#include "my_shell.h"

/**
 * main - entry
 * @argc: cnt for args
 * @argv: pointer for args
 *
 * Return: 0 on success, 1 on error
*/

int main(int argc, char **argv)
{
	int fp = 2; /*initialize file desc. for stderr*/

	if (argc == 2) /*check if 2 arg*/
	{

		fp = open(argv[1], O_RDONLY);

		if (fp == -1) /* check opening smooth*/
		{
			if (errno == EACCES || errno == ENOENT)
			/*permission denied or file not found*/
			{
				perror(argv[1]); /*default error message*/
				exit(EXIT_FAILURE);
			}

		}
		myinfo.rdfd = fp; /*if no error read the file*/
	}

	/**
	* populate_env_list(info);
	read_history(info);
	hsh(info, av);
	*/
	return (EXIT_SUCCESS);
}
