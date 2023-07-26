#ifndef _MY_SHELL_H_
#define _MY_SHELL_H_

/* Constants and macros */

/*alias*/
#define MAX_ALIAS_LEN 100

/* exits */
#define EXIT_PERMISSION_DENIED 126

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
#include <sysexits.h>
#include <fcntl.h>      /* File control options (e.g., open flags). */
#include <limits.h>     /* Limits of various data types. */
#include <errno.h>      /* Error handling and reporting. */
#include <stdbool.h>
#include <signal.h>
#include <ctype.h>

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
 * @env_modify:      Flag indicating if the environment has been modified.
 * @status:       Status of the last executed command.
 * @err_num:      Error code for exit() calls.
 * @histcnt:      History line number count.
 * @line_cnt_flag:Flag to indicate whether to count the current line of input.
 * @line_cnt:     Count of input lines.
 * @argc:         Argument count.
 * @arg:          Input string generated from getline containing arguments.
 * @argv:         Array of strings generated from arg.
 * @path:         String path for the current command.
 * @modified_env: Custom modified copy of the environment variable array.
 * @cmd_buffer:      Pointer to cmd ; chain buffer, for memory management.
 * @fname:        Program filename.
 * @env_list:          local copy of the environment variables.
 * @history:      Linked list representing the history of commands entered.
 * @alias:        Linked list representing aliases for commands.
 */

typedef struct passinfo
{
	int cmd_type;
	int rdfd;
	int env_modify;
	int status;
	int err_num;
	int histcnt;
	int line_cnt_flag;
	unsigned int line_cnt;
	int argc;
	char *arg;
	char **argv;
	char *path;
	char **modified_env;
	char **cmd_buffer;
	char *fname;
	list_s *env_list;
	list_s *history;
	list_s *alias;
} info;


/* Struct definition for builtin commands */

/**
 * struct builtin - built-in command and its function pointer.
 * @cmd: The command string.
 * @func: Pointer to the function implementing the command.
 */
typedef struct builtin
{
	char *cmd;
	int (*func)(info *);
} builtin_cmd;

/*initailization of pass info*/

#define INFO_INIT \
{ \
	0,                 /* cmd_type: CMD_type ||, &&, ; */ \
	0,                 /* rdfd: File descriptor read line input */ \
	0,                 /* env_modify: env modification flag */ \
	0,                 /* status: Status of the last executed command */ \
	0,                 /* err_num: Error code for exit() calls */ \
	0,                 /* histcnt: History line number count */ \
	0,                 /* line_cnt_flag: Flag count line of input */ \
	0,                 /* line_cnt: Count of input lines */ \
	0,                 /* argc: Argument count */ \
	NULL,              /* arg: Input string containing args */ \
	NULL,              /* argv: Array of strings generated from arg */ \
	NULL,              /* path: String path for the current command */ \
	NULL,              /* modified_env: Copy of the environment variables */ \
	NULL,              /* cmd_buffer:cmd ; chain buffer, for memory manage */ \
	NULL,              /* fname: Program filename memory management */ \
	NULL,              /* env_list: Linked list representing copy of env var */ \
	NULL,              /* history: representing the history of commands */ \
	NULL               /* alias: representing aliases for commands */ \
}

info myinfo = INFO_INIT;


/*functions*/

/* my info management*/
void null_info(info *myinfo);
char **create_argv_manually(info *myinfo, char *arg);
void initialize_info(info *myinfo, char **argv);
void myinfo_free(info *myinfo, int freeall);

/*env management*/
char **copy_env(info *myinfo);
int env_new_app(info *myinfo, char *variable, char *value);
int remove_env(info *myinfo, char *var_2be_removed);
int current_env(info *myinfo);
char *search_env_value(info *myinfo, const char *wanted_var);
int new_env(info *myinfo);
int share_env_list(info *myinfo);
int my_unsetenv(info *myinfo);

/*cmd_management*/
int is_cmd_exec(info *myinfo, char *path);
char *duplicate_substring(const char *str, int start, int end);
char *find_cmd_path(info *myinfo, const char *pathstr, const char *command);
void handle_cmd_found(info *myinfo, char *path);
void handle_cmd_not_found(info *myinfo);

/*interactive shell*/
int find_builtin_command(info *myinfo);
void execute_cmd(info *myinfo);
void find_and_execute_cmd(info *myinfo);
int run_shell(info *myinfo, char **argv);

/*builtin_functions*/
int builtin_help(info *myinfo);
int builtin_exit(info *myinfo);
int _cd(info *myinfo);
char *duplicate_substring(const char *str, int start, int end);


/*alias mangment*/
bool unset_alias(info *myinfo, char *alias);
int set_alias(info *myinfo, char *str);
int _myalias(info *myinfo);
int show_history(info *myinfo);
bool show_alias(const list_s *alias_node);

/*history management*/
int write_history(info *myinfo);
char *get_history_file(info *myinfo);
void start_history_list(info *myinfo, char *buf, int line_count);
int renum_history(info *myinfo);

/*read history*/
int open_history_file(const char *filename, ssize_t *file_size);
char *read_history_file(int fd, ssize_t file_size, ssize_t *bytes_read);
int process_history_buffer(info *myinfo, const char *buf, ssize_t bytes_read);
char *extract_command_from_buffer(const char *buf, int start, int end);
int read_history(info *myinfo);

/*getline*/
void control_c(int sig_num);
ssize_t read_buffer(info *myinfo, char *buf, size_t *bytes_read);
ssize_t input_buf(info *myinfo, char **buf, size_t *len);
ssize_t get_input(info *myinfo);
int my_get_next_line(info *myinfo, char **buffer, size_t *size);

/*tokenizer*/
int count_words(const char *str, char delimiter);
char **allocate_memo(int num_words);
int extract_word(const char *str, int i, char delimiter);
char **split_str_to_words(const char *str, char delimiter);


/*stringf1*/
int string_cmp(char *str1, char *str2);
char *str_copy_n(char *destin, const char *sorc, int n);
char *string_dupli(const char *str);
int string_length(char *str);
char *string_cpy(char *destin, const char *sorc);

char *string_concat(char *dest, const char *src);
char *begin_with(const char *haystack, const char *needle);
int put_char(char c);
void print_str(char *input_string);
char *str_concat_n(char *destin, const char *sorc, int n);

/*reallocate*/
void *reallocate(void *ptr, unsigned int old_size, unsigned int new_size);
char *memofill(char *s, char b, unsigned int n);
void funfree(char **pp);
int freememo(void **ptr);

/*linked list*/
size_t print_link_list(const list_s *h);
size_t print_str_list(const list_s *head);
size_t list_length(const list_s *h);
list_s *Add_node_begin(list_s **head, const char *str, int num);
list_s *Add_node_end(list_s **head, const char *str, int num);

ssize_t get_node_index(list_s *head, list_s *node);
char **list_string(list_s *head);
int delete_node(list_s **head, unsigned int index);
list_s *node_starts_with(list_s *head, char *prefix, char c);
void free_link_list(list_s **head_ptr);

/*handle errors*/
int put_char_err(char ch);
int put_char_fd(char ch, int file_d);
int put_str_fd(char *str, int file_d);
void put_str_err(char *str);

char *convert_num(long int num, int base, int flag);
int str_to_int(char *str);
int print_decimal(int num, int file_d);
void remove_comments(char *input_buff);
void print_error(info *info, char *str_err);

/*delimeter*/
void check_chain(info *info, char *buff, size_t *b, size_t a, size_t len);
int chain(info *info, char *buff, size_t *p);
int replace_variables(info *info);
int rep_alias(info *info);
int rep_str(char **old, char *new);

/*convert int*/
int valid_digit_or_whitespace(char c);
int get_sign(const char **str);
unsigned long parse_number(const char *str);
int handle_conversion(char *str);
int convert_to_int(char *str);

/*checks*/
int check_alpha(int character);
int check_delim(char character, char *delim);
int interactive_shell(info *info);
char *str_char(char *str, char target);

static const builtin_cmd builtintbl[] = {
	{"exit", builtin_exit},
	{"env", current_env},
	{"help", builtin_help},
	{"history", show_history},
	{"setenv", new_env},
	{"unsetenv", my_unsetenv},
	{"cd", _cd},
	{NULL, NULL}
};
#endif /* _MY_SHELL_H_ */
