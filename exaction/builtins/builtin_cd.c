#include "../exaction.h"

int builtin_cd(char **args, t_data *data)
{
    if (args[1] && ((ft_strcmp(args[0], "cd") == 0 && !args[1]) || (ft_strcmp(args[0], "cd") == 0 && ft_strcmp(args[1], "~") == 0)))
    {
        char *home_path = getenv("HOME");
        if (!home_path)
        {
            ft_putstr_fd("cd: HOME not set\n", 2);
            return (1);
        }
        chdir(home_path);
        data->name_pro = strdup("➜ ~ ");
        return (0);
    }
    // else if (args[1] && ((ft_strcmp(args[0], "cd") == 0 && ft_strcmp(args[1], ".") == 0)
    //     || (ft_strcmp(args[0], "cd") == 0 && ft_strcmp(args[1], "./") == 0)))
    //     return (0);
    else if (args[1] && ((ft_strcmp(args[0], "cd") == 0 && ft_strcmp(args[1], "..") == 0) || (ft_strcmp(args[0], "cd") == 0 && ft_strcmp(args[1], "../") == 0)))
    {
        char current_path[1024];
        if (chdir("..") < 0)
        {
            perror("Error: ");
            return (-1);
        }
        getcwd(current_path, sizeof(current_path));
        char *new_path = ft_strjoin(current_path, "/");
        if (access(new_path, F_OK) == 0)
        {
            chdir(new_path);
            char **split_path = ft_split(new_path, '/');
            if (!split_path)
                return (-1);
            int i = 0;
            while (split_path[i])
                i++;
            if (i > 0)
                data->name_pro = ft_strjoin(ft_strjoin("➜ ", split_path[i - 1]), " ");
            else
                data->name_pro = ft_strjoin("➜ ", "/ ");
            return (0);
        }
        else
        {
            char *msg_error = ft_strjoin("Error: ", args[1]);
            msg_error = ft_strjoin(msg_error, ": no such file or directory");
            ft_putstr_fd(msg_error, 2);
            ft_putstr_fd("\n", 2);
            return (-1);
        }
        return (0);
    }
    else if (args[1] && (ft_strcmp(args[0], "cd") == 0 && ft_strncmp(args[1], "../", 3) == 0))
    {
        char current_path[1024];
        getcwd(current_path, sizeof(current_path));
        char **split_str = ft_split(args[1], '/');
        if (!split_str)
            return (-1);
        char *new_path = ft_strjoin(current_path, "/");
        new_path = ft_strjoin(new_path, split_str[1]);
            chdir(new_path);
            data->name_pro = ft_strjoin(ft_strjoin("➜ ", split_str[1]), " ");
        // if (access(new_path, F_OK) == 0)
        // {
        //     return (0);
        // }
        // else
        // {
        //     char *msg_error = ft_strjoin("Error: ", args[1]);
        //     msg_error = ft_strjoin(msg_error, ": no such file or directory");
        //     ft_putstr_fd(msg_error, 2);
        //     ft_putstr_fd("\n", 2);
        //     return (-1);
        // }
        return (0);
    }
    else
    {
        char *msg_error = ft_strjoin("Error: cd: ", args[1]);
        msg_error = ft_strjoin(msg_error, ": No such file or directory");
        ft_putstr_fd(msg_error, 2);
        ft_putstr_fd("\n", 2);
        return (-1);
    }
    return (0);
}
