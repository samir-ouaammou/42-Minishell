#include "../../minishell.h"

int builtin_unset(t_ast *node, t_data *data)
{
    int i;
    int j;
    int k;

    if (!node || !data || !data->env)
        return (1);
    i = 1;
    while (node->value[i])
    {
        j = 0;
        while (data->env[j])
        {
            k = 0;
            while (node->value[i][k] && node->value[i][k] != '=')
                k++;
            if (node->value[i][k] == '=')
                return (-1);
            if (ft_strncmp(node->value[i], data->env[j], ft_strlen(node->value[i])) == 0)
            {
                ft_printf("🔴 Unsetting environment variable: %s\n", node->value[i]);
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
    ft_printf("✅ Successfully removed specified environment variables! 👋\n");
    return (0);
}

// int builtin_unset(t_ast *node, t_data *data)
// {
//     if (!node || !data || !data->env)
//         return (1);
//     int i = 1;
//     while (node->value[i])
//     {
//         int j = 0;
//         while (data->env[j])
//         {
//             if (ft_strncmp(node->value[i], data->env[j], ft_strlen(node->value[i])) == 0)
//             {
//                 while (data->env[j + 1])
//                 {
//                     data->env[j] = data->env[j + 1];
//                     j++;
//                 }
//                 data->env[j] = NULL;
//                 break;
//             }
//             j++;
//         }
//         i++;
//     }
//     return (0);
// }
