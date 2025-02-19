/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahaded <aahaded@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 08:43:27 by aahaded           #+#    #+#             */
/*   Updated: 2025/02/17 08:43:30 by aahaded          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	execute_without_left_redirection(int fd_file, char **args,
		t_data *data)
{
	data->stdin_backup = dup(STDIN_FILENO);
	dup2(fd_file, STDIN_FILENO);
	data->status = execute_command(args, data);
	dup2(data->stdin_backup, STDIN_FILENO);
	close(data->stdin_backup);
}

static void	execute_with_redirection(t_ast *node, int fd_file, t_data *data)
{
	int	stdin_backup;

	stdin_backup = dup(STDIN_FILENO);
	dup2(fd_file, STDIN_FILENO);
	execute_ast(node->left, data);
	dup2(stdin_backup, STDIN_FILENO);
	close(stdin_backup);
}

char	**merge_command_args(t_ast *node, int count_left, int count_right)
{
	int		i;
	char	**res;

	res = malloc(sizeof(char *) * (count_left + count_right + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i < count_left)
	{
		res[i] = ft_strdup(node->left->value[i]);
		i++;
	}
	i = 0;
	while (i < count_right)
	{
		res[i + count_left] = ft_strdup(node->right->value[i + 1]);
		i++;
	}
	res[count_left + count_right] = NULL;
	return (res);
}

int	count_args(char **args, int start)
{
	int	count;

	count = 0;
	while (args[start])
	{
		count++;
		start++;
	}
	return (count);
}

int	execute_redir_inp(t_ast *node, t_data *data)
{
	char	**res;

	int(fd_file), (count_left), (count_right);
	fd_file = open_input_file(node);
	if (fd_file == -1)
		return (1);
	if (!node->left)
	{
		res = copy_args(node->right->value, 1, count_args(node->right->value,
					1));
		if (!res)
			return (1);
		execute_without_left_redirection(fd_file, res, data);
	}
	else
	{
		count_left = count_args(node->left->value, 0);
		count_right = count_args(node->right->value, 1);
		res = merge_command_args(node, count_left, count_right);
		if (!res)
			node->left->value = res;
		execute_with_redirection(node, fd_file, data);
	}
	return (0);
}
