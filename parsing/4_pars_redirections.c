#include "../minishell.h"

int ft_check_is_operators(char *str)
{
    if (!str || !str[0])
        return (0);

    return (!ft_strcmp(str, "|") || !ft_strcmp(str, "||") || !ft_strcmp(str, "&&") || !ft_strcmp(str, "(") || !ft_strcmp(str, ")"));
}

int ft_check_is_redirections(char *str)
{
    if (!str || !str[0])
        return (0);

    return (!ft_strcmp(str, "<") || !ft_strcmp(str, ">") || !ft_strcmp(str, "<<") || !ft_strcmp(str, ">>"));
}

char    *ft_move_flags(t_parsing *shell, t_list *list)
{
    t_list  *tmp;
    t_list  *help;
    char    *cmd;
    char    *flg;
    int     i;
    int     j;
    int     k;

    cmd = malloc(ft_strlen(shell->input) + 1);
    flg = malloc(ft_strlen(shell->input) + 1);
    if (!cmd || !flg)
        write(2, "Error: Memory allocation failed.\n", 33);
    cmd[0] = '\0';
    flg[0] = '\0';
    j = 0;
    k = 0;
    tmp = list;
    help = list;
    while (tmp)
    {
        if (tmp && tmp->next  && tmp->next->value[1] && ft_check_is_redirections(tmp->value[0])&& !ft_check_is_redirections(tmp->next->value[0]) )
        {
            i = 0;
            while (tmp->next->value[++i])
            {
                flg = strcat(flg, tmp->next->value[i]);
                flg = strcat(flg, " ");
                // printf("%s ", tmp->next->value[i]);
                tmp->next->value[i] = NULL;
            }
            j++;
        }
        else if ((tmp && tmp->value[1] && !ft_check_is_operators(tmp->value[0]) && !ft_check_is_redirections(tmp->value[0]))
            || (tmp && j == 0 && k == 0 && tmp->next && !tmp->next->value[1] && !ft_check_is_redirections(tmp->value[0])))
        {
            i = -1;
            while (tmp->value[++i])
            {
                flg = strcat(flg, tmp->value[i]);
                flg = strcat(flg, " ");
                // printf("%s ", tmp->value[i]);
                tmp->value[i] = NULL;
            }
            j++;
        }
        if (tmp)
            tmp = tmp->next;
        k++;
    }
    while (help)
    {
        i = 0;
        while (help->value && help->value[i])
        {
            flg = strcat(flg, help->value[i]);
            flg = strcat(flg, " ");
            i++;
        }
        help = help->next;
    }
    printf("%s\n", flg);
    return(cmd);
}

void    ft_pars_redirections(t_parsing *shell, t_list *list)
{
    // (void)list;
    // (void)shell;
    ft_move_flags(shell, list);
    // char *str;
    // t_list  *tmp;
    // size_t     i;
    // int     start;
    // t_list  *help1;
    // t_list  *help2;
    // int     end;
    // help1 = NULL;
    // int     j;
    // int     k;
    // str = malloc(ft_strlen((shell->input) + 1) * sizeof(char *));
    // if (!str)
    // {
    //     write(2, "Error: Memory allocation failed.\n", 33);
    //     exit(-1);
    // }
    // str[0] = '\0';
    // tmp = list;
    // j = 0;
    // while (tmp)
    // {
    //     if (tmp && tmp->next  && tmp->next->value[1] && ft_check_is_redirections(tmp->value[0])&& !ft_check_is_redirections(tmp->next->value[0]) )
    //     {
    //         i = 0;
    //         while (tmp->next->value[++i])
    //         {
    //             printf("%s ", tmp->next->value[i]);
    //             tmp->next->value[i] = NULL;
    //         }
    //         j++;
    //     }
    //     else if ((tmp && tmp->value[1] && !ft_check_is_operators(tmp->value[0]) && !ft_check_is_redirections(tmp->value[0]))
    //         || (tmp && j == 0 && tmp->next && !tmp->next->value[1] && !ft_check_is_redirections(tmp->value[0])))
    //     {
    //         i = -1;
    //         while (tmp->value[++i])
    //         {
    //             printf("%s ", tmp->value[i]);
    //             tmp->value[i] = NULL;
    //         }
    //         j++;
    //     }
    //     if (tmp)
    //         tmp = tmp->next;
    // }
}

