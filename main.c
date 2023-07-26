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
	info *myinfo;
	int file_descriptor = 2; /*initialize file desc. for stderr*/

	if (argc == 2) /*check if 2 arg*/
	{

		file_descriptor = open(argv[1], O_RDONLY);

		if (file_descriptor == -1) /* check opening smooth*/
		{
			if (errno == EACCES || errno == ENOENT)
			/*permission denied or file not found*/
			{
				perror(argv[1]); /*default error message*/
				exit(EXIT_FAILURE);
			}
			else
			{
				perror("error opening file");
				exit(EXIT_FAILURE);
			}

		}
		myinfo->rdfd = file_descriptor; /*if no error read the file*/
	}

	share_env_list(myinfo);
	read_history(myinfo);
	run_shell(myinfo, argv);

	return (EXIT_SUCCESS);
}
