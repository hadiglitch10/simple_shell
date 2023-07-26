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
/* Function to display the command history */
int show_history(info *myinfo)
{
    int count = 1;
    list_s *current = myinfo->history;

    /* If history is empty, display a message */
    if (current == NULL) {
        printf("Command history is empty.\n");
        return 0;
    }

    while (current != NULL) {
        printf("%d: %s\n", count, current->str);
        current = current->nxt;
        count++;
    }

    return (0);
}
info* get_myinfo() {
    return &myinfo;
}
int find_builtin_command(info *myinfo)
{
    char *cmd = myinfo->argv[0];
    int i = 0;

    while (builtintbl[i].cmd != NULL)
    {
        if (strcmp(cmd, builtintbl[i].cmd) == 0)
            return builtintbl[i].func(myinfo);

        i++;
    }

    return (-1); 
}
