#include "../minishell.h"

int ft_is(char c)
{
    if (c == '<' || c == '>' || c == '|' || c == '&')
        return (1);
    return (0);
}

void ft_here_doc(t_parsing *shell, char *str)
{
    char    *line;
    char    *temp;
    char    *help;
    char    c;
    int     i;
    int     j;

    if (!str || !str[0])
        return ;

    i = 0;
    while (str[i])
    {
        if (str[i] == 34 || str[i] == 39)
        {
            c = str[i++];
            while (str[i] && str[i] != c)
                i++;
            if (str[i])
                i++;
        }
        else if (str[i] == '<' && str[i + 1] == '<')
        {
            while (str[i] && str[i] == ' ' || str[i] == '\n')
                i++;
            if (ft_is(str[i]))
                ft_free_args(shell);
            j = i;
            while (str[j] && !ft_is(str[j]))
            {
                if (str[j] == 34 || str[j] == 39)
                {
                    c = str[j++];
                    while (str[j] && str[j] != c)
                        j++;
                }
                if (str[j])
                    j++;
            }
        }
        else
            i++;
    }

}

