#include "./exaction.h"

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
        execve(get_path_env2(cmd[0], data), cmd, NULL);
        dup2(data->stdin_backup, STDIN_FILENO);
        close(data->stdin_backup);
        dup2(data->stdout_backup, STDOUT_FILENO);
        close(data->stdout_backup);
        ft_printf("Minishell: %s: Command not found\n", cmd[0]);
        exit(FAILED);
    }
    else
    {
        wait(&status);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
        {
            data->exit_status = WEXITSTATUS(status);
            return (SUCCESS);
        }
        else
            data->exit_status = 127;
        return (FAILED);
    }
}

int execute_ast(t_ast *root, t_data *data);

int execute_pipe(t_ast *node, t_data *data)
{
    int pipefd[2];
    int(status1), (status2);
    pid_t(pid1), (pid2);
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
        execute_ast(node->left, data);
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
        execute_ast(node->right, data);
        exit(data->status);
    }
    close(pipefd[0]);
    close(pipefd[1]);
    wait(&status1);
    wait(&status2);
    if (WIFEXITED(status2))
        data->status = WEXITSTATUS(status2);
    return (SUCCESS);
}

int check_operator(t_ast *node, t_data *data)
{
    if (!node)
        return (SUCCESS);
    if (ft_strcmp(node->value[0], "exit") == 0)
    {
        ft_printf("exit from program\n");
        exit(EXIT_SUCCESS);
    }
    if (is_operator(node->value[0]))
    {
        if (!node->left || !node->right)
        {
            ft_printf("Error: Parse error near `%s'\n", node->value[0]);
            return (FAILED);
        }
    }
    if (check_operator(node->left, data) == FAILED)
        return (FAILED);
    if (check_operator(node->right, data) == FAILED)
        return (FAILED);
    return (SUCCESS);
}

int fmatch(char *pattern, char *filename)
{
    if (!pattern || !filename)
        return (0);
    if (strcmp(pattern, "*") == 0)
    {
        if (filename[0] == '.')
            return (0);
        else
            return (1);
    }
    if (ft_strncmp(pattern, "*.", 2) == 0)
    {
        char *pattern_ext = pattern + 2;
        char *filename_ext = strrchr(filename, '.');
        if (!filename_ext || strcmp(filename_ext + 1, pattern_ext) != 0)
            return (0);
        else
            return (1);
    }
    return (0);
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
        if (fmatch(str, entry->d_name))
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
        if (fmatch(pattern, entry->d_name))
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
    else if (ft_strcmp(root->value[0], "echo") == 0)
        return (builtin_echo(root->value, data));
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

void execute_redir_out(t_ast *node, t_data *data)
{
    int fd_file = open(node->right->value[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_file == -1)
    {
        perror("Error");
        return;
    }
    data->stdout_backup = dup(STDOUT_FILENO);
    dup2(fd_file, STDOUT_FILENO);
    close(fd_file);
    execute_ast(node->left, data);
    dup2(data->stdout_backup, STDOUT_FILENO);
    close(data->stdout_backup);
}

void execute_redir_inp(t_ast *node, t_data *data)
{
    int fd_file = open(node->right->value[0], O_RDONLY);
    if (fd_file == -1)
    {
        perror("Error");
        return;
    }
    data->stdin_backup = dup(STDIN_FILENO);
    dup2(fd_file, STDIN_FILENO);
    close(fd_file);
    execute_ast(node->left, data);
    dup2(data->stdin_backup, STDIN_FILENO);
    close(data->stdin_backup);
}

// int check_cmd()
// {
//     struct stat fileStat;

//     if (stat("myfile.txt", &fileStat) == 0)
//     {
//         printf("File size: %ld bytes\n", fileStat.st_size);
//         printf("File permissions: %o\n", fileStat.st_mode & 0777);
//         printf("Last modified: %ld\n", fileStat.st_mtime);
//     }
//     else
//     {
//         perror("stat");
//     }
// }

int execute_ast(t_ast *root, t_data *data)
{
    if (!root)
        return (FAILED);
    if (check_operator(root, data) == 1)
        return (FAILED);
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
            execute_redir_out(root, data);
        else if (ft_strcmp(root->value[0], "<") == 0)
            execute_redir_inp(root, data);
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