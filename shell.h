#ifndef SHELL_H
#define SHELL_H

#include <stddef.h>
#include <unistd.h>

/**
 * struct single_list_s - singly linked list
 * @ptr: a malloced address
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 * for ALX shell project
 */
typedef struct single_list_s
{
	void *ptr;
	struct single_list_s *next;
} single_list;

int lnum(int line);

char *get_program_name(char *prog_name);

void print_error(char *error_command, int status, char *others);

void handle_signal(int signal);

void shell_loop(char *file_name);

/* Below find the linked list functions for use with do_memory*/

size_t len_list(single_list *h);

single_list *add_list_node(single_list **head, void *ptr);

single_list *add_list_node_end(single_list **head, void *ptr);

void clear_single_list(single_list *head);

void clear_single_list_all(single_list *head);

single_list *get_list_node_at_index(single_list *head, unsigned int index);

single_list *insert_list_node_at_index(single_list **head, unsigned int index, void *ptr);

int delete_list_node_at_index(single_list **head, unsigned int index);

/* Above find the linked list functions for use with do_memory*/

/**
 * struct list_s2 - singly linked list
 * @ptr: a malloced string
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 * for ALX-Africa shell project
 */
typedef struct list_s2
{
	char *ptr;
	struct list_s2 *next;
} single_list_s;


/* Below find the linked list functions */

size_t list_len(single_list_s *h);

single_list_s *add_node_s(single_list_s **head, char *ptr);

single_list_s *add_node_end_s(single_list_s **head, char *ptr);

void clear_list(single_list_s *head);

void clear_list_all(single_list_s *head);

single_list_s *get_list_node_at_index_s(single_list_s *head, unsigned int index);

single_list_s *insert_list_node_at_index_s(single_list_s **head, unsigned int index, char *ptr);

int delete_list_node_at_index_s(single_list_s **head, unsigned int index);

char **list_to_array(single_list_s *);

single_list_s *array_to_list(char **);

void clear_double_array(char **);

/* Above find the linked list functions */


/* Below find the string functions */

int _strcmp(char *s1, char *s2);

int _strlen(char *s);

int token_count(char *str, char *delim);

char *_strcat(char *s1, char *s2);

char *_strcpy(char *dest, char *src);

int _atoi(char *s);

int sizeof_cmd(char **tokens);

int _isdigit(int c);

int has_newline(char *input);

void shiftbuffer(char *input, int newline_index, int filled);

char *_itoa(int num);

char *_reverse(char *str, int n);

char *_memset(char *s, char b, int n);

/* Above find the string functions */


void *do_memory(size_t size, void *ptr);

void do_exit(int fd, char *msg, int code);

ssize_t else_handle_input(char *lineptr, int stream, char *input, int filled);

ssize_t _getline(char *lineptr, int stream);

char **_strtok(char *str, char *delim);

char **_get_path();

char *get_env_value(char *name);

char *_find_path(char **path, char *command);

char **get_environs();

/* environment functions */

char **do_env(char *x, char *y);

char *get_full_command(char *path, char *command);

/* builtin functions */

int setenv_btin(char **tokens);

int unsetenv_btin(char **tokens);

int cd_btin(char **tokens);

char **get_btin();

int env_btin(void);

/* execute functions */

int execute(char **tokens);

int exec_nbtin(char **tokens);

int search_funcs(char **tokens);

int exec_btin(char **tokens, int bcase);

int check_access(char *comm, char *token);

char *prep_execve(char *token);

/* file functions */

char *read_textfile(char *filename);

#endif /*SHELL_H*/
