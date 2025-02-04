#include "./exaction.h"

int is_operator(char *str)
{
    return (ft_strcmp(str, "|") == 0 || ft_strcmp(str, "||") == 0 || ft_strcmp(str, "&&") == 0 || ft_strcmp(str, ">") == 0 || ft_strcmp(str, "<") == 0 || ft_strcmp(str, "<<") == 0 || ft_strcmp(str, ">>") == 0);
}

int is_builtin(char *cmd)
{
    return (ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "echo") == 0
            // || ft_strcmp(cmd, "env") == 0
            || ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0 || ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "exit") == 0);
}

t_ast *create_node(char **data)
{
    t_ast *node = malloc(sizeof(t_ast));
    if (!node)
    {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    int count = 0;
    while (data[count])
        count++;
    node->value = malloc(sizeof(char *) * (count + 1));
    for (int i = 0; i < count; i++)
        node->value[i] = strdup(data[i]);
    node->value[count] = NULL;

    node->left = NULL;
    node->right = NULL;
    return node;
}

t_ast *build_command_tree(char **tokens, t_data *data, int start, int end)
{
    if (start > end)
        return (NULL);

    if (tokens[start][0] == '(' && tokens[end][0] == ')')
    {
        data->check_parenthese = 1;
        int balance = 1;
        for (int i = start + 1; i < end; i++)
        {
            if (tokens[i][0] == '(')
                balance++;
            else if (tokens[i][0] == ')')
                balance--;
            if (balance == 0)
                break;
        }
        if (balance == 1)
            return build_command_tree(tokens, data, start + 1, end - 1);
    }

    int i;
    int paren_depth = 0;

    i = end;
    while (i >= start)
    {
        if (tokens[i][0] == ')')
            paren_depth++;
        else if (tokens[i][0] == '(')
            paren_depth--;
        if (paren_depth == 0 && ft_strcmp(tokens[i], "<<") == 0)
        {
            t_ast *node = create_node((char *[]){tokens[i], NULL});
            node->left = build_command_tree(tokens, data, start, i - 1);
            node->right = build_command_tree(tokens, data, i + 1, end);
            return node;
        }
        i--;
    }

    i = end;
    paren_depth = 0;
    while (i >= start)
    {
        if (tokens[i][0] == ')')
            paren_depth++;
        else if (tokens[i][0] == '(')
            paren_depth--;
        if (paren_depth == 0 && (is_operator(tokens[i])))
        {
            t_ast *node = create_node((char *[]){tokens[i], NULL});
            node->left = build_command_tree(tokens, data, start, i - 1);
            node->right = build_command_tree(tokens, data, i + 1, end);
            return node;
        }
        i--;
    }

    i = end;
    paren_depth = 0;
    while (i >= start)
    {
        if (tokens[i][0] == ')')
            paren_depth++;
        else if (tokens[i][0] == '(')
            paren_depth--;
        if (paren_depth == 0 && ft_strcmp(tokens[i], "|") == 0)
        {
            t_ast *node = create_node((char *[]){tokens[i], NULL});
            node->left = build_command_tree(tokens, data, start, i - 1);
            node->right = build_command_tree(tokens, data, i + 1, end);
            return node;
        }
        i--;
    }

    return create_node((char *[]){tokens[start], NULL});
}

char **split_input(char *input)
{
    char **tokens = malloc(sizeof(char *) * 20);
    int count = 0;
    char *token = strtok(input, " ");
    while (token && count < 19)
    {
        if (strchr(token, '(') || strchr(token, ')'))
        {
            char *temp = token;
            while (*temp)
            {
                if (*temp == '(' || *temp == ')')
                {
                    tokens[count++] = strndup(temp, 1);
                    temp++;
                }
                else
                {
                    int len = 0;
                    while (temp[len] && temp[len] != '(' && temp[len] != ')')
                        len++;
                    tokens[count++] = strndup(temp, len);
                    temp += len;
                }
            }
        }
        else
            tokens[count++] = strdup(token);
        token = strtok(NULL, " ");
    }
    tokens[count] = NULL;
    return tokens;
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

char *get_path_env2(char *cmd, char **env)
{
    int i;
    int check_path;
    char **path;

    i = 0;
    check_path = 0;
    path = NULL;
    while (env[i])
    {
        if (ft_strncmp(env[i], "PATH=", 5) == 0)
        {
            check_path = 1;
            path = ft_split(env[i] + 5, ':');
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

int execute_command(char **cmd, t_data *data, char **envp)
{
    (void)envp;
    pid_t pid;
    int status;

    pid = fork();
    if (pid == -1)
        return (FAILED);
    else if (pid == 0)
    {
        execve(get_path_env2(cmd[0], envp), cmd, NULL);
        dup2(data->stdin_backup, STDIN_FILENO);
        close(data->stdin_backup);
        dup2(data->stdout_backup, STDOUT_FILENO);
        close(data->stdout_backup);
        ft_printf("Error: Command not found: %s\n", cmd[0]);
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

int execute_ast(t_ast *root, t_data *data, char **env);

int execute_pipe(t_ast *node, t_data *data, char **env)
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
        execute_ast(node->left, data, env);
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
        execute_ast(node->right, data, env);
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
        if (pattern[i] == '$')
        {
            i++;
            char *v = &pattern[i];
            char *val = getenv(v);
            data->matches[*index] = ft_strdup(val);
            (*index)++;
            break;
        }
        i++;
    }
    return (0);
}

int check_wildcards_Dollar(char **args, t_data *data, char **env)
{
    (void)data;
    (void)env;
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
            expand_Dollar(args[i], data, &match_index);
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
            if (args[i][j] == '*' || args[i][j] == '$')
                return (1);
            // else if (args[i][j] == '$')
            //     return (2);
            j++;
        }
        i++;
    }
    return (0);
}

int execute_builtin(t_ast *root, t_data *data, char **env)
{
    (void)data;
    (void)env;
    if (ft_strcmp(root->value[0], "pwd") == 0)
        return (builtin_pwd());
    else if (ft_strcmp(root->value[0], "echo") == 0)
        return (builtin_echo(root->value, data));
    else if (ft_strcmp(root->value[0], "unset") == 0)
        return (builtin_unset(root, data));
    else if (ft_strcmp(root->value[0], "export") == 0)
        return (builtin_export(root, data));
    return (0);
}

void execute_redir_out(t_ast *node, t_data *data, char **env)
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
    execute_ast(node->left, data, env);
    dup2(data->stdout_backup, STDOUT_FILENO);
    close(data->stdout_backup);
}

void execute_redir_inp(t_ast *node, t_data *data, char **env)
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
    execute_ast(node->left, data, env);
    dup2(data->stdin_backup, STDIN_FILENO);
    close(data->stdin_backup);
}

int execute_ast(t_ast *root, t_data *data, char **env)
{
    (void)data;
    (void)env;
    if (!root)
        return (FAILED);
    if (check_operator(root, data) == 1)
        return (FAILED);
    if (is_operator(root->value[0]))
    {
        if (ft_strcmp(root->value[0], "&&") == 0)
        {
            execute_ast(root->left, data, env);
            if (data->status == 0)
                execute_ast(root->right, data, env);
        }
        else if (ft_strcmp(root->value[0], "||") == 0)
        {
            execute_ast(root->left, data, env);
            if (data->status != 0)
                execute_ast(root->right, data, env);
        }
        else if (ft_strcmp(root->value[0], "|") == 0)
            execute_pipe(root, data, env);
        else if (ft_strcmp(root->value[0], ">") == 0)
            execute_redir_out(root, data, env);
        else if (ft_strcmp(root->value[0], "<") == 0)
            execute_redir_inp(root, data, env);
    }
    else if (is_builtin(root->value[0]))
        data->status = execute_builtin(root, data, env);
    else
    {
        if (check_special_chars(root->value, data) == 1)
        {
            check_wildcards_Dollar(root->value, data, env);
            data->status = execute_command(data->matches, data, env);
        }
        else
            data->status = execute_command(root->value, data, env);
    }
    return (data->status);
}

void print_tree(t_ast *root, int depth)
{
    if (root == NULL)
        return;
    for (int i = 0; i < depth; i++)
        printf("  ");
    printf("Node: %s\n", root->value[0]);
    print_tree(root->left, depth + 1);
    print_tree(root->right, depth + 1);
}

int ft_strlen_2d(char **arr)
{
    int len = 0;

    while (arr[len] != NULL)
        len++;
    return (len);
}

t_ast *create_complex_command_tree()
{
    char *cmd1[] = {"cat", NULL};
    char *cmd2[] = {"<", NULL};
    char *cmd3[] = {"file_test", NULL};
    // char *cmd4[] = {"wc", "-l", NULL};
    // char *cmd5[] = {"ls", NULL};
    //  char *cmd6[] = {"ls", NULL};
    //  char *cmd7[] = {"ls", NULL};
    t_ast *root = create_node(cmd2);
    root->left = create_node(cmd1);
    root->right = create_node(cmd3);
    // root->left->left = create_node(cmd3);
    // root->left->right = create_node(cmd5);
    //  root->right->left = create_node(cmd4);
    //  root->right->right = create_node(cmd5);
    return (root);
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
    read_env(data, envp);
    builtin_exit(root);
    execute_ast(root, data, data->env);
    // int i = 0;
    // while (data->env[i])
    // {
    //     printf("%s\n", data->env[i]);
    //     i++;
    // }
}

// int main(int argc, char **argv, char **envp)
// {
//     (void)argc;
//     (void)argv;
//     (void)envp;
//     char *input;
//     while (1)
//     {
//         input = readline("minishell > ");
//         if (!input)
//             break;
//         add_history(input);
//         char **tokens = split_input(input);
//         // chdir("/home/aahaded");
//         t_data data = {NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
//         data.matches = NULL;
//         t_ast *root = build_command_tree(tokens, &data, 0, ft_strlen_2d(tokens) - 1);
//         // t_ast *root = create_complex_command_tree();
//         // print_tree(root, 0);
//         exaction(root, &data, envp);
//     }
//     return 0;
// }