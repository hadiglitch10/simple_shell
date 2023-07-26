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
	info *myinfo = INFO_INIT;
	int file_descriptor = 2; /*initialize file desc. for stderr*/
	myinfo = (info *)malloc(sizeof(info)); /* allocate memory for info struct */

	if (myinfo == NULL) /* check if malloc was successful */
	{
		perror("Error: Unable to allocate memory");
		return (EXIT_FAILURE);
	}
		null_info(myinfo); /* initialize the info struct */
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
	run_shell(myinfo);
	myinfo_free(myinfo, 1);
	return (EXIT_SUCCESS);
}
