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
    t_list  *help;
    char    *redirections;
    int     i;
    int     j;
    int     k;

    redirections = malloc(ft_strlen(shell->input) + 1);
    if (!redirections)
        write(2, "Error: Memory allocation failed.\n", 33);
    redirections[0] = '\0';
    j = 0;
    k = 0;
    help = list;
    while (list)
    {
        if (list && list->value && ft_check_is_operators(list->value[0]))
            break;
        if (list && list->next  && list->next->value[1] && ft_check_is_redirections(list->value[0])&& !ft_check_is_redirections(list->next->value[0]) )
        {
            i = 0;
            while (list->next->value[++i])
            {
                redirections = strcat(redirections, list->next->value[i]);
                redirections = strcat(redirections, " ");
                list->next->value[i] = NULL;
            }
            j++;
        }
        else if ((list && list->value[1] && !ft_check_is_operators(list->value[0]) && !ft_check_is_redirections(list->value[0]))
            || (list && j == 0 && k == 0 && list->next && !list->next->value[1] && !ft_check_is_redirections(list->value[0])))
        {
            i = -1;
            while (list->value[++i])
            {
                redirections = strcat(redirections, list->value[i]);
                redirections = strcat(redirections, " ");
                list->value[i] = NULL;
            }
            j++;
        }
        if (list)
            list = list->next;
        k++;
    }
    while (help)
    {
        if (help && help->value && ft_check_is_operators(help->value[0]))
            break;
        i = 0;
        while (help->value && help->value[i])
        {
            redirections = strcat(redirections, help->value[i]);
            redirections = strcat(redirections, " ");
            i++;
        }
        help = help->next;
    }
    redirections[ft_strlen(redirections) - 1] = '\0';
    return(redirections);
}

void    ft_pars_redirections(t_parsing *shell, t_list *list)
{
    t_list  *tmp;
    t_list  *help;
    t_list  *help2;
    t_list  *start;
    char    *str;
    char    *redirections;
    int     i;
    int     j;

    str = malloc(strlen(shell->input));
    if (!str)
        write(2, "Error: Memory allocation failed.\n", 33);
    str[0] = '\0';
    tmp = list;
    help = NULL;
    j = 0;
    while (tmp)
    {
        if ((!tmp->value[1] && ft_check_is_redirections(tmp->value[0]))
            || (help && help->value && !help->value[1] && ft_check_is_redirections(help->value[0])))
        {
            if (help && !ft_check_is_operators(help->value[0]))
                start = help;  
            else
                start = tmp;
            redirections = ft_move_flags(shell, start);
            str = strcat(str, redirections);
            str = strcat(str, " ");
            free(redirections);
            while (tmp && !ft_check_is_operators(tmp->value[0]))
                tmp = tmp->next;
            if (tmp && tmp->value && ft_check_is_operators(tmp->value[0]))
            {
                j = 42;
                str = strcat(str, tmp->value[0]);
                str = strcat(str, " ");
                if (tmp)
                    tmp = tmp->next;
                if (tmp && !tmp->next && !ft_check_is_redirections(tmp->value[0]))
                {
                    i = 0;
                    while (tmp && tmp->value[i])
                    {
                        str = strcat(str, tmp->value[i]);
                        str = strcat(str, " ");
                        i++;
                    }
                }
                    
            }
            else if (tmp)
                tmp = tmp->next;
        }
        i = 0;
        while (j == 0 && tmp && tmp->value && tmp->value[i] && tmp->next && !ft_check_is_redirections(tmp->next->value[0]))
        {
            str = strcat(str, tmp->value[i]);
            str = strcat(str, " ");
            i++;
        }
        help2 = help;
        help = tmp;
        if (tmp)
            tmp = tmp->next;
        j = 0;
    }
    if (help2 && help2->value && ft_check_is_operators(help2->value[0]))
    {
        i = 0;
        while(help && help->value && help->value[i])
        {
            str = strcat(str, help->value[i]);
            str = strcat(str, " ");
            i++;
        }
    }
    if (list && list->value && !list->next)
    {
        tmp = list;
        i = 0;
        while(tmp && tmp->value && tmp->value[i])
        {
            str = strcat(str, tmp->value[i]);
            str = strcat(str, " ");
            i++;
        }
    }
    ft_free_parsing(shell);
    shell->input = str;
}

