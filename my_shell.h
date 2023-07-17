#ifndef _MY_SHELL_H_
#define _MY_SHELL_H_

/* Constants and macros */

/* Buffer sizes for reading and writing */
#define BUFFER_SIZE 1024
#define BUFFER_FLUSH -1

/* Command chaining */
#define CMD_NORMAL 0
#define CMD_OR_OPERATOR 1
#define CMD_AND_OPERATOR 2
#define CMD_CHAIN_OPERATOR 3

/* Convert number . */
#define CONVERT_TO_LOWERCASE 1
#define CONVERT_TO_UNSIGNED 2

/* Flags  custom getline and strtok functions  */
#define USE_CUSTOM_GETLINE 0
#define USE_CUSTOM_STRTOK 0

/* File name and maximum size for command history storage. */
#define HISTORY_FILE ".my_shell_history"
#define MAX_HISTORY_SIZE 4096

/* Standard library includes */

#include <stdio.h>      /* Input/Output functions printf and scanf. */
#include <stdlib.h>     /* Memory allocation  */
#include <unistd.h>     /* System call functions like fork, exec, and chdir. */
#include <string.h>     /* functions like strcmp and strtok. */
#include <sys/types.h>  /* Data types used in system calls. */
#include <sys/wait.h>   /* Waiting for child processes. */
#include <sys/stat.h>   /* File status and mode definitions. */
#include <fcntl.h>      /* File control options (e.g., open flags). */
#include <limits.h>     /* Limits of various data types. */
#include <errno.h>      /* Error handling and reporting. */

/* External variables */
extern char **environ;





/*structs*/

/* one for linked lists */
/**
 * struct lnkdstr - singly linked list
 * @numf: num field
 * @str: string
 * @nxt: pointer next node
 */

typedef struct lnkdstr
{
	struct lnkdstr *nxt; /*pointer to the nexxt node*/
	int numf; /*num of feilds*/
	char *str; /*string holder*/

} list_s;

/*one for the arguments*/

/**
 * struct passinfo - Contains pseudo-arguments to pass into a function,
 * @cmd_type:     (CMD_NORMAL, CMD_OR, CMD_AND, CMD_CHAIN).
 * @rdfd:         File descriptor from which to read line input.
 * @env_mod:      Flag indicating if the environment has been modified.
 * @status:       Status of the last executed command.
 * @err_num:      Error code for exit() calls.
 * @histcnt:      History line number count.
 * @line_cnt_flag:Flag to indicate whether to count the current line of input.
 * @line_cnt:     Count of input lines.
 * @argc:         Argument count.
 * @arg:          Input string generated from getline containing arguments.
 * @argv:         Array of strings generated from arg.
 * @path:         String path for the current command.
 * @env:          Custom modified copy of the environment variable array.
 * @cmd_buf:      Pointer to cmd ; chain buffer, for memory management.
 * @fname:        Program filename.
 * @env:          local copy of the environment variables.
 * @history:      Linked list representing the history of commands entered.
 * @alias:        Linked list representing aliases for commands.
 */

typedef struct passinfo
{
	int cmd_type;    /* CMD_type ||, &&, ; */
	int rdfd;          /* File descriptor from which to read line input */
	int env_mod;     /* env modification flag */
	int status; /*status of the last executed command */
	int err_num;         /* Error code for exit() calls */
	int histcnt;       /* History line number count */
	int line_cnt_flag;  /* Flag to count the current line of input */
	unsigned int line_cnt; /* Count of input lines */

	int argc;            /* Argument count */
	char *arg;           /* Input string from getline contain arguments */
	char **argv;         /* Array of strings generated from arg */

	char *path;          /* String path for the current command */
	char **env;      /* Custom modified copy of the environment variable array */
	char **cmd_buf;      /* Pointer to cmd ; chain buffer, for */
	char *fname;       /* Program filename memory management */


	list_s *env;         /* Linked list representing copy env var */
	list_s *history;     /*  representing the history of commands */
	list_s *alias;       /*  representing aliases for commands */
} info;

/* Struct definition for builtin commands */

/**
 * struct builtin - built in commands
 * @b_cmd: str cmd
 * @fp: func point cmd
*/
typedef struct builtin
{
	int (*fp)(info *);   /* Function pointer builtin command */
	char *b_cmd;                  /* String representing the builtin command */

} builtin_cmd;

/*initailization of pass info*/

#define INFO_INIT \
{ \
	0,                 /* cmd_type: CMD_type ||, &&, ; */ \
	0,                 /* infd: File descriptor read line input */ \
	0,                 /* env_mod: env modification flag */ \
	0,                 /* status: Status of the last executed command */ \
	0,                 /* err_num: Error code for exit() calls */ \
	0,                 /* histcnt: History line number count */ \
	0,                 /* line_cnt_flag: Flag count line of input */ \
	0,                 /* line_cnt: Count of input lines */ \
	0,                 /* argc: Argument count */ \
	NULL,              /* arg: Input string  containing args */ \
	NULL,              /* argv: Array of strings generated from arg */ \
	NULL,              /* path: String path for the current command */ \
	NULL,              /* env:copy of the environment variables */ \
	NULL,              /* cmd_buf: Pointer cmd chain buffer mem manage */ \
	NULL,              /* fname: Program filename */ \
	NULL,              /* env: local copy of env variables */ \
	NULL,              /* history:  history of commands entered */ \
	NULL               /* alias:  aliases for commands */ \
}

info myinfo = INFO_INIT;


/*functions*/

#endif /* _MY_SHELL_H_ */
