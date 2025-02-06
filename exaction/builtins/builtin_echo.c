#include "../exaction.h"

int builtin_echo(char **str, t_data *data)
{
    (void)data;
    int i = 1;
    int quots = 2;
    int newline = 0;
    int check = 0;
    char *value = NULL;

    if (!str || !str[0])
        return (0);
    while (str[i] && ft_strcmp(str[i], "-n") == 0)
    {
        check = 1;
        i++;
    }
    int count_arg = 1;
    while (str[count_arg])
        count_arg++;
    char **new_args = malloc(sizeof(char *) * (count_arg + 1));
    if (!new_args)
        return (0);
    i = 1;
    while (str[i])
    {
        char *ss = ft_check_quots(str[i], &quots, &newline, data->input);
        // char *ss = "test";
        int j = 0;
        if (quots == 1)
            ft_putstr(ss);
        else if (quots == 2)
        {
            j = 0;
            while (ss[j])
            {
                if (ss[j] == '$' && ss[j + 1] == '?')
                {
                    ft_putnbr_fd(data->exit_status, 1);
                    j += 2;
                    if (ss[j])
                        ft_putstr_fd(&ss[j], 1);
                    break;
                }
                else if (ss[j] == '$')
                {
                    j++;
                    value = getenv(&ss[j]);
                    if (value)
                        ft_putstr_fd(value, 1);
                    else
                        ft_putstr_fd("", 1);
                    break;
                }
                else
                    ft_putchar(ss[j]);
                j++;
            }
        }
        // if (newline == 1)
        //     write(1, " ", 1);
        // free(ss);
        i++;
    }
    if (!check)
        ft_putchar_fd('\n', 1);
    return (1);
}
