/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahaded <aahaded@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 08:45:18 by aahaded           #+#    #+#             */
/*   Updated: 2025/02/17 08:45:21 by aahaded          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int a = 3;

int ft_test(t_ast *node, t_data *data)
{
    (void)data;
    if (!node || !node->left || !node->right || !node->left->value[0] || !node->right->value[0])
        return (0);
    int e2 = ft_test(node->left, data);
    if (e2 == -1)
        return (-1);
    if (ft_strcmp(node->value[0], ">") == 0)
    {
        data->fd_file = open(node->right->value[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (data->fd_file == -1)
        {
            ft_printf("Error\n");
            return (-1);
        }
        // if (a != 0)
        // {
        //     a -= 1;
        ft_printf("value: %s\n", node->right->value[0]);
        pid_t pid = fork();
        if (pid == -1)
        {
            ft_printf("minishell: fork failed\n");
            close(data->fd_file);
            return (FAILED);
        }
        else if (pid == 0)
        {
            dup2(data->fd_file, STDOUT_FILENO);
            close(data->fd_file);
            data->status = execute_ast(node->left, data);
            exit(data->status);
        }
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            data->status = WEXITSTATUS(status);
        close(data->fd_file);
        // }
    }

    return (0);
}

int execute_redir_RightArrow_redirout(t_ast *node, t_data *data, char *type)
{
    int fd = ft_test(node, data);
    (void)type;
    (void)fd;
    return (1);
    pid_t pid = fork();
    if (pid == -1)
    {
        ft_printf("minishell: fork failed\n");
        close(data->fd_file);
        return (FAILED);
    }
    else if (pid == 0)
    {
        dup2(data->fd_file, STDOUT_FILENO);
        close(data->fd_file);
        data->status = execute_ast(node->left, data);
        exit(data->status);
    }
    int status;
    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
        data->status = WEXITSTATUS(status);
    close(data->fd_file);
    return (0);
}