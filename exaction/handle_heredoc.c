/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahaded <aahaded@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:50:08 by aahaded           #+#    #+#             */
/*   Updated: 2025/02/17 18:50:10 by aahaded          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static void execute_without_left_heredoc(int fd_file, char **args, t_data *data)
// {
//     int stdinp_backup;

//     stdinp_backup = dup(STDIN_FILENO);
//     dup2(fd_file, STDIN_FILENO);
//     data->status = execute_command(args, data);
//     dup2(stdinp_backup, STDIN_FILENO);
//     close(stdinp_backup);
// }

static void execute_with_heredoc(t_ast *node, int fd_file, t_data *data)
{
    int stdinp_backup;

    stdinp_backup = dup(STDIN_FILENO);
    dup2(fd_file, STDIN_FILENO);
    execute_ast(node->left, data);
    dup2(stdinp_backup, STDIN_FILENO);
    close(stdinp_backup);
}

int execute_heredoc(t_ast *node, t_data *data)
{
    int fd_file, (count_left), (count_right);
    char **res;

    fd_file = open_input_file(node);
    if (fd_file == -1)
        return (1);
    // if (!node->left)
    // {
    //     res = copy_args(node->right->value, 1, count_args(node->right->value, 1));
    //     if (!res)
    //         return (1);
    //     execute_without_left_heredoc(fd_file, res, data);
    // }
    // else
    {
        count_left = count_args(node->left->value, 0);
        count_right = count_args(node->right->value, 1);
        res = merge_command_args(node, count_left, count_right);
        node->left->value = res;
        execute_with_heredoc(node, fd_file, data);
    }
    return (0);
}