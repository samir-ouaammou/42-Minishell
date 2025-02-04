#ifndef EXACTION_H
#define EXACTION_H

#include <dirent.h>
#include <fnmatch.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "../libft/libft.h"
#include "../parsing/Minishell.h"
// #include "./pipex/pipex.h"

#define SUCCESS 0
#define FAILED 1

// typedef struct s_node
// {
//     char **data;
//     struct s_node *left;
//     struct s_node *right;
// } t_node;

typedef struct s_data
{
    char **matches;
    char **DollarSign;
    char **env;
    int status;
    int exit_status;
    int check_operator;
    int check_parenthese;
    int check_pipe;
    int check_exe;
    int check_fmatch;
    int save_index;
    int stdout_backup;
    int stdin_backup;
    int err_status;
} t_data;

void exaction(t_ast *root, t_data *data, char **envp);
int builtin_exit(t_ast *node);
int builtin_pwd();
int builtin_echo(char **str, t_data *data);
int builtin_unset(t_ast *node, t_data *data);
int builtin_export(t_ast *node, t_data *data);

#endif