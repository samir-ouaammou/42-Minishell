#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>


typedef struct s_parsing
{
    int     i;
    int     j;
    int     bol;
    int     len;
    int     free;
    int     parentheses;
    char    chr;
    char    *cmds;
    char    *input;
    char    **cmds_split;

}   t_parsing;


void    ft_parsing(t_parsing *shell);
void    ft_free_all(t_parsing *shell);
void    ft_split_args(t_parsing *shell);
void    ft_delete_commits(t_parsing *shell);

#endif
