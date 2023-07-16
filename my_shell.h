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

/* Function prototypes (if applicable) */
/* void function_name(void); */

#endif /* _MY_SHELL_H_ */
