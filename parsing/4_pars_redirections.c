#include "../minishell.h"


char    *ft_move_flags(t_parsing *shell, t_list *list)
{
    t_list  *help;
    char    *redirections;
    int     i;
    int     j;
    int     k;

    redirections = ft_malloc(ft_strlen(shell->input) + 1);
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
                redirections = ft_strjoin_and_free(redirections, list->next->value[i]);
                redirections = ft_strjoin_and_free(redirections, " ");
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
                redirections = ft_strjoin_and_free(redirections, list->value[i]);
                redirections = ft_strjoin_and_free(redirections, " ");
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
            redirections = ft_strjoin_and_free(redirections, help->value[i]);
            redirections = ft_strjoin_and_free(redirections, " ");
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
    char    *str;
    char    *redirections;
    int     i;

    str = ft_malloc(ft_strlen(shell->input));
    if (!str)
    {
        write(2, "Error: Memory allocation failed.\n", 33);
        ft_exit(-1);
    }
    str[0] = '\0';
    tmp = list;
    help = NULL;
    while (tmp)
    {
        i = 0;
        while (tmp && tmp->value && ft_check_is_operators(tmp->value[0]))
        {
            i = 0;
            while (tmp && tmp->value[i])
            {
                str = ft_strjoin_and_free(str, tmp->value[i]);
                str = ft_strjoin_and_free(str, " ");
                i++;
            }
            tmp = tmp->next;
        }
        while (tmp && tmp->value && !ft_check_is_operators(tmp->value[0]) && !ft_check_is_redirections(tmp->value[0]))
        {
            i = 0;
            while (tmp && tmp->value[i])
            {
                str = ft_strjoin_and_free(str, tmp->value[i]);
                str = ft_strjoin_and_free(str, " ");
                i++;
            }
            tmp = tmp->next;
        }
        if (tmp && tmp->value && ft_check_is_redirections(tmp->value[0]))
        {
            i = 42;
            help = tmp;
            redirections = ft_move_flags(shell, help);
            str = ft_strjoin_and_free(str, redirections);
            str = ft_strjoin_and_free(str, " ");
            while (tmp && tmp->value && !ft_check_is_operators(tmp->value[0]))
                tmp = tmp->next;
        }
        if (tmp && i == 0)
            tmp = tmp->next;
    }
    ft_free_parsing(shell);
    ft_init_parsing(shell);
    shell->input = str;
}
