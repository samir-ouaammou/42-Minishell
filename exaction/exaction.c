#include "../minishell.h"

int is_operator(char *str)
{
    return (ft_strcmp(str, "|") == 0 || ft_strcmp(str, "||") == 0 || ft_strcmp(str, "&&") == 0 || ft_strcmp(str, ">") == 0 || ft_strcmp(str, "<") == 0 || ft_strcmp(str, "<<") == 0 || ft_strcmp(str, ">>") == 0);
}

int is_builtin(char *cmd)
{
    return (ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "env") == 0 || ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0 || ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "exit") == 0);
}

char *get_path_env_utils2(char **path, char *cmd)
{
    char *path_arg;
    int i;

    i = 0;
    while (path[i])
    {
        path_arg = ft_strjoin(path[i], "/");
        path_arg = ft_strjoin(path_arg, cmd);
        if (access(path_arg, X_OK) == 0)
            return (path_arg);
        i++;
    }
    return (NULL);
}

char *get_path_env2(char *cmd, t_data *data)
{
    int i;
    int check_path;
    char **path;

    i = 0;
    check_path = 0;
    path = NULL;
    while (data->env[i])
    {
        if (ft_strncmp(data->env[i], "PATH=", 5) == 0)
        {
            check_path = 1;
            path = ft_split(data->env[i] + 5, ':');
            break;
        }
        i++;
    }
    if (!check_path)
        return (NULL);
    else if (cmd == NULL || is_operator(cmd))
        return (NULL);
    else if (get_path_env_utils2(path, cmd))
        return (get_path_env_utils2(path, cmd));
    return (NULL);
}

int execute_command(char **cmd, t_data *data)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == -1)
        return (FAILED);
    else if (pid == 0)
    {
        struct stat statbuf;
        if (stat(cmd[0], &statbuf) == 0 && S_ISDIR(statbuf.st_mode))
        {
            fprintf(stderr, "Error: %s: Is a directory\n", cmd[0]);
            exit(126);
        }
        int i = 0;
        int check_ = 0;
        while (cmd[0][i])
        {
            if (cmd[0][i] == '/')
                check_++;
            i++;
        }
        if ((get_path_env2(cmd[0], data) != NULL) && check_ != 1 && cmd[0][1] != '/')
            execve(get_path_env2(cmd[0], data), cmd, data->env);
        else
        {
            if (access(cmd[0], F_OK) == 0)
            {
                if (access(cmd[0], X_OK) == 0)
                    execve(cmd[0], cmd, data->env);
                else
                {
                    fprintf(stderr, "Error: %s: Permission denied\n", cmd[0]);
                    exit(126);
                }
            }
            else
            {
                if (check_)
                {
                    fprintf(stderr, "Error: %s: No such file or directory\n", cmd[0]);
                    exit(127);
                }
                else
                {
                    fprintf(stderr, "Error: %s: Command not found\n", cmd[0]);
                    exit(127);
                }
            }
        }
        return (FAILED);
    }
    else
    {
        wait(&status);
        if (WIFEXITED(status))
        {
            if (WEXITSTATUS(status) == 0)
            {
                data->exit_status = 0;
                return (SUCCESS);
            }
            else if (WEXITSTATUS(status) == 126)
            {
                data->exit_status = 126;
                return (FAILED);
            }
            else if (WEXITSTATUS(status) == 127)
            {
                data->exit_status = 127;
                return (FAILED);
            }
            else
                data->exit_status = 2;
        }
        return (FAILED);
    }
}

int execute_ast(t_ast *root, t_data *data);
int execute_pipe(t_ast *node, t_data *data)
{
    int pipefd[2];
    int status1, status2;
    pid_t pid1, pid2;

    if (pipe(pipefd) == -1)
        return (FAILED);
    pid1 = fork();
    if (pid1 == -1)
        return (FAILED);
    if (pid1 == 0)
    {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        if (execute_ast(node->left, data) == FAILED)
            exit(EXIT_FAILURE);
        exit(data->status);
    }
    pid2 = fork();
    if (pid2 == -1)
        return (FAILED);
    if (pid2 == 0)
    {
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        if (execute_ast(node->right, data) == FAILED)
            exit(EXIT_FAILURE);
        exit(data->status);
    }
    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(pid1, &status1, 0);
    waitpid(pid2, &status2, 0);
    if (WIFEXITED(status1) && WIFEXITED(status2))
        data->status = WEXITSTATUS(status2);
    else
        data->status = FAILED;
    return (SUCCESS);
}

int count_flag(char *pattern)
{
    int i = 0;
    int count = 0;
    if (!pattern)
        return (0);
    while (pattern[i])
    {
        if (pattern[i] == '*')
            count++;
        i++;
    }
    if (count == 0)
        return (1);
    return (0);
}

int count_flag_Dollar(char *pattern)
{
    int i = 0;
    int count = 0;
    if (!pattern)
        return (0);
    while (pattern[i])
    {
        if (pattern[i] == '$')
            count++;
        i++;
    }
    if (count == 0)
        return (1);
    return (0);
}

int count_wildcards(char *str)
{
    DIR *dir;
    struct dirent *entry;
    int count = 0;

    dir = opendir(".");
    if (!dir)
        return (1);
    while ((entry = readdir(dir)) != NULL)
    {
        if (ft_match_pattern(str, entry->d_name))
            count++;
    }
    closedir(dir);
    return (count);
}

int expand_wildcards(char *pattern, t_data *data, int *index)
{
    DIR *dir;
    struct dirent *entry;

    dir = opendir(".");
    if (!dir)
        return (1);
    while ((entry = readdir(dir)) != NULL)
    {
        if (ft_match_pattern(pattern, entry->d_name))
        {
            data->matches[*index] = ft_strdup(entry->d_name);
            (*index)++;
        }
    }
    closedir(dir);
    return (0);
}

int expand_Dollar(char *pattern, t_data *data, int *index)
{
    int i = 0;

    while (pattern[i])
    {
        if (pattern[i] == '$' && pattern[i] != '\0')
        {
            i++;
            char *v = &pattern[i];
            char *val = getenv(v);
            if (!val)
                return (-1);
            data->matches[*index] = ft_strdup(val);
            (*index)++;
            break;
        }
        i++;
    }
    return (0);
}

int check_wildcards_Dollar(char **args, t_data *data)
{
    (void)data;
    int i = 0;
    int count = 0;

    while (args[i])
    {
        if (count_flag(args[i]) == 0)
            count += count_wildcards(args[i]);
        else if (count_flag_Dollar(args[i]) == 0)
            count++;
        i++;
    }
    data->matches = malloc(sizeof(char *) * (count + 1));
    if (!data->matches)
        return (-1);
    i = 0;
    int match_index = 0;
    while (args[i])
    {
        if (count_flag(args[i]) == 0)
            expand_wildcards(args[i], data, &match_index);
        else if (count_flag_Dollar(args[i]) == 0)
        {
            if (expand_Dollar(args[i], data, &match_index) == -1)
                data->err_status = -1;
            else
                data->err_status = 0;
        }
        else
        {
            data->matches[match_index] = ft_strdup(args[i]);
            match_index++;
        }
        i++;
    }
    data->matches[match_index] = NULL;
    return (0);
}

int check_special_chars(char **args, t_data *data)
{
    (void)data;
    int i = 0;
    while (args[i])
    {
        int j = 0;
        while (args[i][j])
        {
            if (args[i][j] == '$' && args[i][j + 1] == '\0')
                return (0);
            else if (args[i][j] == '*' || args[i][j] == '$')
                return (1);
            j++;
        }
        i++;
    }
    return (0);
}

int execute_builtin(t_ast *root, t_data *data)
{
    (void)data;
    if (ft_strcmp(root->value[0], "pwd") == 0)
        return (builtin_pwd());
    // else if (ft_strcmp(root->value[0], "echo") == 0)
    //     return (builtin_echo());
    else if (ft_strcmp(root->value[0], "unset") == 0)
        return (builtin_unset(root, data));
    else if (ft_strcmp(root->value[0], "export") == 0)
        return (builtin_export(root, data));
    else if (ft_strcmp(root->value[0], "cd") == 0)
        return (builtin_cd(root->value, data));
    else if (ft_strcmp(root->value[0], "env") == 0)
        return (builtin_env(root->value, data));
    return (0);
}

// void execute_redir_out(t_ast *node, t_data *data)
// {
//     int fd_file = open(node->right->value[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
//     if (fd_file == -1)
//     {
//         perror("Error");
//         return;
//     }
//     int count_left = 0;
//     if (!node->left)
//     {
//         int i = 1;
//         int count = 0;
//         while (node->right->value[i])
//         {
//             count++;
//             i++;
//         }
//         char **res = malloc(sizeof(char *) * (count + 1));
//         if (!res)
//             return;
//         i = 1;
//         int j = 0;
//         while (j < count)
//         {
//             res[j] = ft_strdup(node->right->value[i]);
//             j++;
//             i++;
//         }
//         res[i] = NULL;
//         int new_fd = dup(STDOUT_FILENO);
//         dup2(fd_file, STDOUT_FILENO);
//         close(fd_file);
//         execute_command(res, data);
//         dup2(new_fd, STDOUT_FILENO);
//         close(new_fd);
//     }
//     else
//     {
//         while (node->left->value[count_left])
//             count_left++;
//         int i = 1;
//         int count_right = 0;
//         while (node->right->value[i])
//         {
//             count_right++;
//             i++;
//         }
//         char **res = malloc(sizeof(char *) * ((count_left + count_right) + 1));
//         if (!res)
//             return;
//         i = 0;
//         while (i < count_left)
//         {
//             res[i] = ft_strdup(node->left->value[i]);
//             i++;
//         }
//         i = 1;
//         while (node->right->value[i])
//         {
//             res[i + count_left - 1] = ft_strdup(node->right->value[i]);
//             i++;
//         }
//         res[count_left + count_right] = NULL;
//         node->left->value = res;
//         data->stdout_backup = dup(STDOUT_FILENO);
//         dup2(fd_file, STDOUT_FILENO);
//         close(fd_file);
//         execute_ast(node->left, data);
//         dup2(data->stdout_backup, STDOUT_FILENO);
//         close(data->stdout_backup);
//     }
// }

void execute_redir_inp(t_ast *node, t_data *data)
{
    (void)data;
    int fd_file = open(node->right->value[0], O_RDONLY);
    if (fd_file == -1)
    {
        perror("Error");
        return;
    }
    if (!node->left)
    {
        int i = 1;
        int count = 0;
        while (node->right->value[i])
        {
            count++;
            i++;
        }
        char **res = malloc(sizeof(char *) * (count + 1));
        if (!res)
            return;
        i = 1;
        int j = 0;
        while (j < count)
        {
            res[j] = ft_strdup(node->right->value[i]);
            j++;
            i++;
        }
        res[j] = NULL;
        data->stdin_backup = dup(STDIN_FILENO);
        dup2(fd_file, STDIN_FILENO);
        data->status = execute_command(res, data);
        dup2(data->stdin_backup, STDIN_FILENO);
        close(data->stdin_backup);
    }
    else
    {
        int count_left = 0;
        while (node->left->value[count_left])
            count_left++;
        int i = 1;
        int count_right = 0;
        while (node->right->value[i])
        {
            count_right++;
            i++;
        }
        char **res = malloc(sizeof(char *) * ((count_left + count_right) + 1));
        if (!res)
            return;
        i = 0;
        while (i < count_left)
        {
            res[i] = ft_strdup(node->left->value[i]);
            i++;
        }
        i = 1;
        while (node->right->value[i])
        {
            res[i + count_left - 1] = ft_strdup(node->right->value[i]);
            i++;
        }
        res[count_left + count_right] = NULL;

        node->left->value = res;
        int stdin_backup = dup(STDIN_FILENO);
        dup2(fd_file, STDIN_FILENO);
        execute_ast(node->left, data);
        dup2(stdin_backup, STDIN_FILENO);
        close(stdin_backup);
    }
}

void execute_redir_RightArrow_redirout(t_ast *node, t_data *data, char *type)
{
    (void)data;
    int fd_file = 0;
    if (ft_strcmp(type, "RightArrow") == 0)
    {
        fd_file = open(node->right->value[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd_file == -1)
        {
            perror("Error");
            return;
        }
    }
    else if (ft_strcmp(type, "redirout") == 0)
    {
        fd_file = open(node->right->value[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd_file == -1)
        {
            perror("Error");
            return;
        }
    }
    int count_left = 0;
    int stdout_backup = dup(STDOUT_FILENO);
    dup2(fd_file, STDOUT_FILENO);
    close(fd_file);
    if (!node->left)
    {
        int i = 1;
        int count = 0;
        while (node->right->value[i])
        {
            count++;
            i++;
        }
        char **res = malloc(sizeof(char *) * (count + 1));
        if (!res)
            return;
        i = 1;
        int j = 0;
        while (j < count)
        {
            res[j] = ft_strdup(node->right->value[i]);
            j++;
            i++;
        }
        res[i] = NULL;
        // int new_fd = dup(STDOUT_FILENO);
        // dup2(fd_file, STDOUT_FILENO);
        // close(fd_file);
        data->status = execute_command(res, data);
        // dup2(new_fd, STDOUT_FILENO);
        // close(new_fd);
    }
    else
    {
        while (node->left->value[count_left])
            count_left++;
        int i = 1;
        int count_right = 0;
        while (node->right->value[i])
        {
            count_right++;
            i++;
        }
        char **res = malloc(sizeof(char *) * ((count_left + count_right) + 1));
        if (!res)
            return;
        i = 0;
        while (i < count_left)
        {
            res[i] = ft_strdup(node->left->value[i]);
            i++;
        }
        i = 1;
        while (node->right->value[i])
        {
            res[i + count_left - 1] = ft_strdup(node->right->value[i]);
            i++;
        }
        res[count_left + count_right] = NULL;
        node->left->value = res;
        execute_ast(node->left, data);
    }
    dup2(stdout_backup, STDOUT_FILENO);
    close(stdout_backup);
}

char *ft_strcpy(char *dest, char *src)
{
    int i = 0;
    while (src[i])
    {
        dest[i] = src[i];
        i++;
    }
    return (dest);
}

char *get_str_Dollars(char *str)
{
    int len = 0;
    int i = 1;
    while (str[i])
    {
        if (str[i] != '$')
            len++;
        i++;
    }
    char *res = malloc(len + 1);
    if (!res)
        return (NULL);
    i = 1;
    int j = 0;
    while (str[i])
    {
        if (str[i] != '$')
            res[j++] = str[i];
        else
            break;
        i++;
    }
    res[j] = '\0';
    return (res);
}

char *find_str_env(char *str, t_data *data)
{
    if (!str || !data->env)
        return (NULL);
    int i = 0;
    while (data->env[i])
    {
        if (ft_strncmp(data->env[i], str, ft_strlen(str)) == 0)
            return (data->env[i]);
        i++;
    }
    return (NULL);
}

int process_strings(t_ast *root, t_data *data)
{
    if (!root || !root->value || !data)
        return (-1);
    int count = 0;
    while (root->value[count])
        count++;
    char **res = malloc(sizeof(char *) * (count + 1));
    if (!res)
        return (-1);
    int i = 0;
    while (i < count)
    {
        int x = 0;
        size_t len = 0;

        while (root->value[i][x])
        {
            if (root->value[i][x] == '$' && root->value[i][x + 1] != '?')
            {
                char *str = get_str_Dollars(&root->value[i][x]);
                if (str)
                {
                    len += ft_strlen(str);
                    char *s1 = find_str_env(ft_strjoin(str, "="), data);
                    if (s1)
                    {
                        char *chrstr_path = ft_strchr(s1, '=');
                        if (chrstr_path)
                            len += ft_strlen(chrstr_path);
                    }
                }
                x += ft_strlen(str) + 1;
            }
            else if (root->value[i][x] == '$' && root->value[i][x + 1] == '?')
            {
                char *str = ft_itoa(data->exit_status);
                if (str)
                    len += ft_strlen(str);
                x += 2;
            }
            else
            {
                len += 1;
                x++;
            }
        }
        res[i] = malloc(len + 1);
        if (!res[i])
            return (-1);
        x = 0;
        int y = 0;
        while (root->value[i][x])
        {
            if (root->value[i][x] == '$' && root->value[i][x + 1] != '?')
            {
                char *str = get_str_Dollars(&root->value[i][x]);
                if (str)
                {
                    char *s1 = find_str_env(ft_strjoin(str, "="), data);
                    if (s1)
                    {
                        char *chrstr = ft_strchr(s1, '=');
                        if (chrstr)
                        {
                            ft_strcpy(&res[i][y], chrstr + 1);
                            y += ft_strlen(chrstr) - 1;
                        }
                    }
                }
                x += ft_strlen(str) + 1;
            }
            else if (root->value[i][x] == '$' && root->value[i][x + 1] == '?')
            {
                char *str = ft_itoa(data->exit_status);
                if (str)
                {
                    ft_strcpy(&res[i][y], str);
                    y += ft_strlen(str);
                }
                x += 2;
            }
            else
            {
                res[i][y] = root->value[i][x];
                y++;
                x++;
            }
        }
        res[i][y] = '\0';
        i++;
    }
    res[count] = NULL;
    root->value = res;
    return (0);
}

int execute_ast(t_ast *root, t_data *data)
{
    if (!root)
        return (FAILED);
    process_strings(root, data);
    if (is_operator(root->value[0]))
    {
        if (ft_strcmp(root->value[0], "&&") == 0)
        {
            execute_ast(root->left, data);
            if (data->status == 0)
                execute_ast(root->right, data);
        }
        else if (ft_strcmp(root->value[0], "||") == 0)
        {

            execute_ast(root->left, data);
            if (data->status != 0)
                execute_ast(root->right, data);
        }
        else if (ft_strcmp(root->value[0], "|") == 0)
            execute_pipe(root, data);
        else if (ft_strcmp(root->value[0], ">") == 0)
            execute_redir_RightArrow_redirout(root, data, "redirout");
        else if (ft_strcmp(root->value[0], "<") == 0)
            execute_redir_inp(root, data);
        else if (ft_strcmp(root->value[0], ">>") == 0)
            execute_redir_RightArrow_redirout(root, data, "RightArrow");
    }
    else if (is_builtin(root->value[0]))
        data->status = execute_builtin(root, data);
    else
    {
        
        if (check_special_chars(root->value, data) == 1)
        {
            check_wildcards_Dollar(root->value, data);
            if (data->err_status != -1)
                data->status = execute_command(data->matches, data);
            else
                data->status = 0;
        }
        else
        
            data->status = execute_command(root->value, data);
        // printf("status: %d\n", data->status);
    }
    return (data->status);
}

void read_env(t_data *data, char **envp)
{
    if (!*envp)
        return;
    int count = 0;
    while (envp[count])
        count++;
    data->env = malloc(sizeof(char *) * (count + 1));
    if (!data->env)
        return;
    int i = 0;
    while (envp[i])
    {
        data->env[i] = envp[i];
        i++;
    }
    data->env[count] = NULL;
}

void exaction(t_ast *root, t_data *data, char **envp)
{
    (void)root;
    (void)envp;
    data->err_status = 0;
    builtin_exit(root);
    execute_ast(root, data);
    // int i = 0;
    // while (data->env[i])
    // {
    //     printf("-> %s\n", data->env[i]);
    //     i++;
    // }
}
