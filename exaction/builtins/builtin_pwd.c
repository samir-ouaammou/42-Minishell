#include "../../minishell.h"

int builtin_pwd(void)
{
    char path[1024];
    if (getcwd(path, sizeof(path)))
    {
        ft_printf("%s\n", path);
        return (0);
    }
    else
    {
        perror("minishell: pwd: error");
        return (1);
    }
}
