#include "../exaction.h"

int builtin_echo(char **str, t_data *data)
{
    int i = 1;
    int check = 0;
    char *value = NULL;

    if (!str || !str[0])
        return (0);
    while (str[i] && ft_strcmp(str[i], "-n") == 0)
    {
        check = 1;
        i++;
    }
    while (str[i])
    {
        if (str[i][0] == '\'')
            ft_putstr_fd(str[i], 1);
        else
        {
            int j = 0;
            while (str[i][j])
            {
                if (str[i][j] == '$' && str[i][j + 1] == '?')
                {
                    ft_putnbr_fd(data->exit_status, 1);
                    j += 2;
                    if (str[i][j])
                        ft_putstr_fd(&str[i][j], 1);
                    break;
                }
                else if (str[i][j] == '$')
                {
                    j++;
                    if ((value = getenv(&str[i][j])))
                        ft_putstr_fd(value, 1);
                    else
                        ft_putstr_fd("", 1);
                    break;
                }
                else
                    ft_putchar_fd(str[i][j], 1);
                j++;
            }
        }
        if (str[i + 1])
            ft_putstr_fd(" ", 1);
        i++;
    }
    if (!check)
        ft_putstr_fd("\n", 1);
    return (1);
}
