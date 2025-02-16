#include "../minishell.h"

int builtin_echo(char **str, t_data *data)
{
    (void)data;
    int     i;
    size_t     j;
    int     newline;

    if (!str || !str[0])
        return (1);
    i = 1;
    j = 1;
    newline = 1;
    if (str[1][0] == '-' && str[1][1] == 'n')
    {
        while (str[1][0] == '-' && str[1][j] == 'n')
            j++;
        if (j == ft_strlen(str[1]))
        {
            newline = 0;
            i = 2;
        }
    }
    while (str[i])
    {
        ft_putstr_fd(str[i], 2);
        if (str[i + 1])
            write (2, " ", 1);
        i++;
    }
    if (newline)
        write (1, "\n", 1);
    return (0);
}
