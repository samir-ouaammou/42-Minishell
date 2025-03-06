
#include "../minishell.h"

int execute_redirection(t_ast *root, t_exaction *data)
{
    if (!root)
        return (0);

    int i = 0;
    int fd_out = -1;
    int fd_in = -1;
    if (ft_strcmp(root->value[0], ">") == 0)
    {
        fd_out = open(root->right->value[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd_out == -1)
        {
            ft_printf("minishell: %s: %s\n", root->right->value[0], strerror(errno));
            data_struc()->exit_status = 1;
            return (1);
        }
    }
    else if (ft_strcmp(root->value[0], "<") == 0)
    {
        fd_in = open(root->right->value[0], O_RDONLY);
        if (fd_in == -1)
        {
            ft_printf("minishell: %s: %s\n", root->right->value[0], strerror(errno));
            data_struc()->exit_status = 1;
            return (1);
        }
    }
    else if (ft_strcmp(root->value[0], ">>") == 0)
    {
        fd_out = open(root->right->value[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd_out == -1)
        {
            ft_printf("minishell: %s: %s\n", root->right->value[0], strerror(errno));
            data_struc()->exit_status = 1;
            return (1);
        }
    }
    while (root->right->value[i])
    {
        if (ft_strcmp(root->right->value[i], ">") == 0)
        {
            i++;
            fd_out = open(root->right->value[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd_out == -1)
            {
                ft_printf("minishell: %s: %s\n", root->right->value[i], strerror(errno));
                data_struc()->exit_status = 1;
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
                data_struc()->exit_status = 1;
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
                data_struc()->exit_status = 1;
                return (1);
            }
        }
        i++;
    }

    pid_t pid = fork();
    if (pid == -1)
    {
        ft_printf("minishell: fork\n");
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
        data_struc()->status = execute_ast(root->left, data);
        ft_exit(data_struc()->status);
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            data_struc()->status = WEXITSTATUS(status);
        if (fd_out != -1)
            close(fd_out);
        if (fd_in != -1)
            close(fd_in);
    }
    return (0);
}