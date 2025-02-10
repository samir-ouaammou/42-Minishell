#include "../../minishell.h"

int builtin_cd(char **args, t_data *data)
{
    char    *cd;
    char    *str;
    char    *tmp;
    char    path[10000];

    if (!args || !args[0])
        return (-1);
    if (args[2])
    {
        write(2, "minishell: cd: too many arguments\n", 34);
        return (1);
    }
    else if (args[0] && !args[1])
        cd = getenv("HOME");
    else
        cd = args[1];
    if (chdir(cd) == -1)
    {
        perror("minishell: cd");
        return (-1);
    }
    getcwd(path, sizeof(path));
    if (path[0] == '/' && path[1] == '\0')
        str = ft_strdup("➜ /");
    else
        str = ft_strjoin("➜ ", ft_strrchr(path, '/') + 1);
    tmp = ft_strjoin(str, " ");
    free(str);
    data->name_pro = tmp;
    return (0);
}

// int builtin_cd(char **args, t_data *data)
// {
//     (void)data;
//     if (args[2])
//     {
//         ft_printf("Error: cd: too many arguments\n");
//         return (-1);
//     }
//     if ((args[0] && (ft_strcmp(args[0], "cd") == 0 && !args[1])) || (ft_strcmp(args[0], "cd") == 0 && ft_strcmp(args[1], "~") == 0))
//     {
//         char *home_path = getenv("HOME");
//         if (!home_path)
//         {
//             ft_putstr_fd("cd: HOME not set\n", 2);
//             return (1);
//         }
//         chdir(home_path);
//         data->name_pro = strdup("➜ ~ ");
//         return (0);
//     }
//     else if (chdir(args[1]) <= -1)
//     {
//         ft_printf("Error: cd: %s: No such file or directory\n", args[1]);
//         return (-1);
//     }
//     else
//     {
//         char buffer[10000];
//         getcwd(buffer, sizeof(buffer));
//         char *str = ft_strrchr(buffer, '/');
//         if (str[0] == '/' && str[1] != '\0')
//         {
//             char *str_j = ft_strjoin("➜ ", str + 1);
//             str_j = ft_strjoin(str_j, " ");
//             data->name_pro = str_j;
//         }
//         else
//             data->name_pro = "➜ / ";
//     }
//     return (0);
// }

