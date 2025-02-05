#include "../exaction.h"

int builtin_cd(char **args, t_data *data)
{
    if ((ft_strcmp(args[0], "cd") == 0 && !args[1]) || (ft_strcmp(args[0], "cd") == 0 && ft_strcmp(args[1], "~") == 0))
    {
        char *home_path = getenv("HOME");
        if (!home_path)
        {
            ft_putstr_fd("cd: HOME not set\n", 2);
            return (1);
        }
        chdir(home_path);
        free(data->name_pro);
        data->name_pro = strdup("➜ ~ ");
        return (0);
    }
    if (args[1] && ((ft_strcmp(args[0], "cd") == 0 && ft_strcmp(args[1], "..") == 0) || (ft_strcmp(args[0], "cd") == 0 && ft_strcmp(args[1], "../") == 0)))
    {
        char current_path[1024];
        if (chdir("..") < 0)
        {
            perror("Error: ");
            return (-1);
        }
        getcwd(current_path, sizeof(current_path));
        char *new_path = strdup(current_path);
        new_path = ft_strjoin(new_path, "/");
        if (access(new_path, F_OK) == 0)
        {
            chdir(new_path);
            char **split_path = ft_split(new_path, '/');
            if (!split_path)
                return (0);
            int i = 0;
            while (split_path[i])
                i++;
            if (i > 0)
                data->name_pro = ft_strjoin(ft_strjoin("➜  ", split_path[i - 1]), " ");
            else
                data->name_pro = ft_strjoin("➜  ", "/ ");
        }
        else
        {
            char *msg_error = ft_strjoin("Error: ", args[1]);
            msg_error = ft_strjoin(msg_error, ": no such file or directory");
            ft_putstr_fd(msg_error, 2);
            ft_putstr_fd("\n", 2);
        }
    }
    else
    {
        char *msg_error = ft_strjoin("Error: ", args[1]);
        msg_error = ft_strjoin(msg_error, ": no such file or directory");
        ft_putstr_fd(msg_error, 2);
        ft_putstr_fd("\n", 2);
    }
    // else if (((ft_strlen(str) == ft_strlen("cd ..")) || (ft_strlen(str) == ft_strlen("cd ../"))) && (ft_strncmp(str, "cd ..", ft_strlen("cd ..")) == 0 || ft_strncmp(str, "cd ../", ft_strlen("cd ../")) == 0))
    // {
    //     char s[1024];
    //     char *path_;
    //     char *change_path;
    //     char **split_str;
    //     int i;

    //     i = 0;
    //     chdir("..");
    //     path_ = getcwd(s, sizeof(s));
    //     split_str = ft_split(path_, '/');
    //     while (split_str[i])
    //         i++;
    //     if (i > 0)
    //         i--;
    //     else
    //         split_str[i] = path_;
    //     change_path = ft_strjoin("\033[0;92m➜\033[0;39m\033[1m\033[96m  ", split_str[i]);
    //     change_path = ft_strjoin(change_path, "\033[0;39m ");
    //     data.name_pro = change_path;
    //     i--;
    // }
    // else if ((ft_strlen(str) == ft_strlen("cd")) && (ft_strncmp(str, "cd", ft_strlen("cd")) == 0 || ft_strncmp(str, "cd ~", ft_strlen("cd ~")) == 0))
    // {
    //     char *home_path;

    //     home_path = getenv("HOME");
    //     chdir(home_path);
    //     data.name_pro = "\033[0;92m➜\033[0;39m\033[1m\033[96m  ~\033[0;39m ";
    // }
    return (0);
}
