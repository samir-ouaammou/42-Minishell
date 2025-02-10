#include "../../minishell.h"

int is_numeric(const char *str)
{
    int i = 0;

    if (!str || !str[0])
        return (0);
    if (str[i] == '-' || str[i] == '+')
        i++;
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}

int builtin_exit(t_ast *node)
{
    int exit_code = 0;

    if (!node)
        return (SUCCESS);
    if (ft_strcmp(node->value[0], "exit") == 0)
    {
        ft_printf("exit\n");
        if (node->value[1])
        {
            exit_code = ft_atoi(node->value[1]);
            if (is_numeric(node->value[1]) && node->value[2])
            {
                ft_printf("❌ minishell: exit: too many arguments\n");
                exit (2);
            }
            if (!is_numeric(node->value[1]) && !node->value[2])
            {
                ft_printf("❌ minishell: exit: %s: numeric argument required\n", node->value[1]);
                exit(2);
            }
        }
        ft_printf("✅ Goodbye! Have a great day! 👋\n");
        exit(exit_code);
    }
    return (SUCCESS);
}


// int builtin_exit(t_ast *node)
// {
//     if (!node)
//         return (SUCCESS);
//     if (ft_strcmp(node->value[0], "exit") == 0)
//     {
//         ft_printf("exit from program\n");
//         exit(EXIT_SUCCESS);
//     }
//     if (builtin_exit(node->left) == FAILED)
//         return (FAILED);
//     if (builtin_exit(node->right) == FAILED)
//         return (FAILED);
//     return (SUCCESS);
// }
