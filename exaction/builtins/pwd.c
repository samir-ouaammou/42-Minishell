#include "../exaction.h"

int builtin_pwd()
{
    char buffer[1024];
    if (getcwd(buffer, sizeof(buffer)))
    {
        ft_printf("%s\n", buffer);
        return (1);
    }
    else
        perror("pwd error");
    return (0);
}