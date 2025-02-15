#include "../minishell.h"

void    ft_remove_tab(char **str)
{
    int     i;
    int     j;
    int     k;

    if (!str || !str[0])
        return ;
    i = 0;
    while (str[i])
    {
        j = 0;
        while (str[i][j])
        {
            if (str[i][j] == '\t')
            {
                k = j;
                while (str[i][k])
                {
                    str[i][k] = str[i][k + 1];
                    k++;
                }
            }
            else
                j++;
        }
        i++;
    }
}

void ft_remove_quots(char **str)
{
    int     i;
    int     j;
    char    c;

    if (!str || !str[0])
        return ;
    i = 0;
    while (str[i])
    {
        j = 0;
        while (str[i][j])
        {
            if (str[i][j] == 34 || str[i][j] == 39)
            {
                c = str[i][j];
                str[i][j] = '\t';
                while (c != str[i][j])
                    j++;
                str[i][j] = '\t';
            }
            j++;
        }
        i++;
    }
    ft_remove_tab(str);
}
