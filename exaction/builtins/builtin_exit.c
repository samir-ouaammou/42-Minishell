#include "../../minishell.h"

int builtin_exit(t_ast *node)
{
    if (!node)
        return (SUCCESS);
    if (ft_strcmp(node->value[0], "exit") == 0)
    {
        ft_printf("exit from program\n");
        exit(EXIT_SUCCESS);
    }
    if (builtin_exit(node->left) == FAILED)
        return (FAILED);
    if (builtin_exit(node->right) == FAILED)
        return (FAILED);
    return (SUCCESS);
}