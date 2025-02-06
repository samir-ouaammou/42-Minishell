#include "../../minishell.h"

int builtin_unset(t_ast *node, t_data *data)
{
    if (!node || !data || !data->env)
        return (1);
    int i = 1;
    while (node->value[i])
    {
        int j = 0;
        while (data->env[j])
        {
            if (ft_strncmp(node->value[i], data->env[j], ft_strlen(node->value[i])) == 0)
            {
                while (data->env[j + 1])
                {
                    data->env[j] = data->env[j + 1];
                    j++;
                }
                data->env[j] = NULL;
                break;
            }
            j++;
        }
        i++;
    }
    return (0);
}