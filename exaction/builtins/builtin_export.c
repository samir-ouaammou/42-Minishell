#include "../../minishell.h"

int builtin_export(t_ast *node, t_data *data)
{
    if (!node || !data || !data->env)
        return (1);
    int i = 1;
    while (node->value[i])
    {
        char *str = ft_strchr(node->value[i], '=');
        if (!str)
        {
            i++;
            continue;
        }
        int j = 0;
        int found = 0;
        while (data->env[j])
        {
            if (ft_strncmp(data->env[j], node->value[i], (str - node->value[i])) == 0)
            {
                data->env[j] = ft_strdup(node->value[i]);
                found = 1;
                break;
            }
            j++;
        }
        if (!found)
        {
            int count = 0;
            while (data->env[count])
                count++;
            char **new_env = malloc(sizeof(char *) * (count + 2));
            if (!new_env)
                return (1);
            int k = 0;
            while (data->env[k])
            {
                new_env[k] = data->env[k];
                k++;
            }
            new_env[k] = ft_strdup(node->value[i]);
            new_env[k + 1] = NULL;
            data->env = new_env;
        }
        i++;
    }
    return (0);
}
