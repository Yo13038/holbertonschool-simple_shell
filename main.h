#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

int main(int ac, char **av, char **env);
void shell_loop(char **env);
int is_empty_line(char *line);
void remove_newline(char *line);
int handle_builtin(char **argv, char **env, char *line);
void builtin_exit(char **argv, char *line);
int builtin_env(char **env);
char **parse_line(char *line);
char *_getenv(const char *name);
int contains_slash(char *command);
char *find_command(char *command);
char *build_path(char *dir, char *cmd);
int is_executable_command(char *path);
int execute_command(char *path, char **argv, char **env);
void free_args(char **argv);
int _strlen(char *s);
int _strcmp(char *s1, char *s2);
int _strncmp(char *s1, char *s2, int n);
char *_strcpy(char *dest, char *src);
char *_strdup(char *s);

#endif
