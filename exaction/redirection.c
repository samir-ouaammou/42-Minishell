
#include "../minishell.h"

int execute_redirection(t_ast *root, t_exaction *data)
{
    if (!root)
        return (0);

    int i = 0;
    int fd_out = -1;
    int fd_in = -1;
    char **str_arr = NULL;
    char **str_sa = NULL;
    if (!root || !root->value)
        return (1);
    if (root->right && root->right->value)
    {
        str_sa = malloc(sizeof(char *) * (2));
        if (!str_sa)
            return (1);
        str_sa[0] = root->right->value[0];
        str_sa[1] = NULL;
        ft_remove_quots(str_sa, data, 0);
        if (str_sa[0][0] == '$')
        {
            ft_printf("minishell: %s: ambiguous redirect\n", root->right->value[0]);
            data->exit_status = 1;
            free_all(str_sa);
            return (1);
        }
        i = 0;
        str_arr = malloc(sizeof(char *) * (2));
        if (!str_arr)
        {
            if (str_sa)
                free_all(str_sa);
            return (1);
        }
        str_arr[0] = root->right->value[0];
        str_arr[1] = NULL;
        ft_remove_quots(str_arr, data, 1);
        if (ft_strcmp(root->value[0], ">") == 0)
        {
            fd_out = open(str_arr[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd_out == -1)
            {
                ft_printf("minishell: %s: %s\n", str_arr[0], strerror(errno));
                free_all(str_arr);
                if (str_sa)
                    free_all(str_sa);
                data->exit_status = 1;
                return (1);
            }
        }
        else if (ft_strcmp(root->value[0], "<") == 0)
        {
            fd_in = open(str_arr[0], O_RDONLY);
            if (fd_in == -1)
            {
                ft_printf("minishell: %s: %s\n", str_arr[0], strerror(errno));
                free_all(str_arr);
                if (str_sa)
                    free_all(str_sa);
                data->exit_status = 1;
                return (1);
            }
        }
        else if (ft_strcmp(root->value[0], ">>") == 0)
        {
            fd_out = open(str_arr[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd_out == -1)
            {
                ft_printf("minishell: %s: %s\n", str_arr[0], strerror(errno));
                free_all(str_arr);
                if (str_sa)
                    free_all(str_sa);
                data->exit_status = 1;
                return (1);
            }
        }
    }
    else
        return (1);
    while (root->right->value[i])
    {
        if (ft_strcmp(root->right->value[i], ">") == 0)
        {
            i++;
            fd_out = open(root->right->value[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd_out == -1)
            {
                ft_printf("minishell: %s: %s\n", root->right->value[i], strerror(errno));
                if (str_arr)
                    free_all(str_arr);
                if (str_sa)
                    free_all(str_sa);
                data->exit_status = 1;
                return (1);
            }
        }
        else if (ft_strcmp(root->right->value[i], ">>") == 0)
        {
            i++;
            fd_out = open(root->right->value[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd_out == -1)
            {
                ft_printf("minishell: %s: %s\n", root->right->value[i], strerror(errno));
                if (str_arr)
                    free_all(str_arr);
                if (str_sa)
                    free_all(str_sa);
                data->exit_status = 1;
                return (1);
            }
        }
        else if (ft_strcmp(root->right->value[i], "<") == 0)
        {
            i++;
            fd_in = open(root->right->value[i], O_RDONLY);
            if (fd_in == -1)
            {
                ft_printf("minishell: %s: %s\n", root->right->value[i], strerror(errno));
                if (str_arr)
                    free_all(str_arr);
                if (str_sa)
                    free_all(str_sa);
                data->exit_status = 1;
                return (1);
            }
        }
        i++;
    }
    i = 0;
    int count = 0;
    while (root->left->value[i])
    {
        if (root->left->value[i][0] == '$')
        {
            char *str = process_strings(root->left->value[i], data);
            if (str)
            {
                char **split_str = ft_split(str, ' ');
                if (!split_str)
                {
                    if (str_arr)
                        free_all(str_arr);
                    if (str_sa)
                        free_all(str_sa);
                    return (free(str), 1);
                }
                int j = 0;
                while (split_str[j])
                    j++;
                count += j;
                free(str);
                free_all(split_str);
            }
        }
        else
            count++;
        i++;
    }
    char **res = malloc(sizeof(char *) * (count + 1));
    if (!res)
    {
        if (str_arr)
            free_all(str_arr);
        if (str_sa)
            free_all(str_sa);
        return (1);
    }
    i = 0;
    count = 0;
    int k = 0;
    while (root->left->value[i])
    {
        if (root->left->value[i][0] == '$')
        {
            char *str = process_strings(root->left->value[i], data);
            if (str)
            {
                char **split_str = ft_split(str, ' ');
                if (!split_str)
                {
                    if (str_arr)
                        free_all(str_arr);
                    return (free(str), 1);
                }
                int j = 0;
                while (split_str[j])
                {
                    res[k++] = ft_strdup(split_str[j]);
                    j++;
                }
                free(str);
                free_all(split_str);
            }
            i++;
        }
        else
            res[k++] = root->left->value[i++];
    }
    res[k] = NULL;
    root->left->value = res;
    pid_t pid = fork();
    if (pid == -1)
    {
        ft_printf("minishell: fork\n");
        if (str_arr)
            free_all(str_arr);
        if (str_sa)
            free_all(str_sa);
        return (1);
    }
    else if (pid == 0)
    {
        if (fd_out != -1)
        {
            dup2(fd_out, STDOUT_FILENO);
            close(fd_out);
        }
        if (fd_in != -1)
        {
            dup2(fd_in, STDIN_FILENO);
            close(fd_in);
        }
        data->status = execute_ast(root->left, data);
        exit(data->status);
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            data->status = WEXITSTATUS(status);
        if (fd_out != -1)
            close(fd_out);
        if (fd_in != -1)
            close(fd_in);
    }
    if (str_arr)
        free_all(str_arr);
    if (str_sa)
        free_all(str_sa);
    return (0);
}