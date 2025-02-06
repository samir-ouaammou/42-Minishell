#include "../../minishell.h"

int builtin_env(char **args, t_data *data)
{
    if (!data->env)
        return (-1);
    if (args[1])
    {
        printf("Error\n");
        return (-1);
    }
    int i = 0;
    while (data->env[i])
    {
        ft_putstr(data->env[i]);
        ft_putchar('\n');
        i++;
    }
    return (0);
}