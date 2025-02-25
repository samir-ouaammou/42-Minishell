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

// static void execute_without_left_redirection(int fd_file2, char **args,
// 											 t_data *data)
// {
// 	data->stdin_backup = dup(STDIN_FILENO);
// 	dup2(fd_file, STDIN_FILENO);
// 	data->status = execute_command(args, data);
// 	dup2(data->stdin_backup, STDIN_FILENO);
// 	close(data->stdin_backup);
// }

// static void execute_with_redirection(t_ast *node, int fd_file, t_data *data)
// {
// 	int stdin_backup;

// 	stdin_backup = dup(STDIN_FILENO);
// 	dup2(fd_file, STDIN_FILENO);
// 	execute_ast(node->left, data);
// 	dup2(stdin_backup, STDIN_FILENO);
// 	close(stdin_backup);
// }

// char **merge_command_args(t_ast *node, int count_left, int count_right)
// {
// 	int i;
// 	char **res;

// 	res = malloc(sizeof(char *) * (count_left + count_right + 1));
// 	if (!res)
// 		return (NULL);
// 	i = 0;
// 	while (i < count_left)
// 	{
// 		res[i] = ft_strdup(node->left->value[i]);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < count_right)
// 	{
// 		res[i + count_left] = ft_strdup(node->right->value[i + 1]);
// 		i++;
// 	}
// 	res[count_left + count_right] = NULL;
// 	return (res);
// }

// int count_args(char **args, int start)
// {
// 	int count;

// 	count = 0;
// 	while (args[start])
// 	{
// 		count++;
// 		start++;
// 	}
// 	return (count);
// }

int execute_redir_inp(t_ast *node, t_data *data)
{
	if (data->check_file_2 == 0)
	{
		data->name_path_file2 = ft_strdup(node->right->value[0]);
		if (!data->name_path_file2)
		{
			ft_printf("minishell: memory allocation failed\n");
			return (FAILED);
		}
	}
	data->fd_file2 = open(data->name_path_file2, O_RDONLY);
	if (data->fd_file2 == -1)
	{
		ft_printf("minishell: %s: %s\n", data->name_path_file2, strerror(errno));
		return (FAILED);
	}
	if (data->check_file_2 != 0)
	{
		int d = open_input_file(node);
		if (d == -1)
			return (FAILED);
	}
	data->check_file_2 = 1;
	pid_t pid = fork();
	if (pid == -1)
	{
		ft_printf("minishell: fork failed\n");
		close(data->fd_file2);
		return (FAILED);
	}
	else if (pid == 0)
	{
		dup2(data->fd_file2, STDIN_FILENO);
		close(data->fd_file2);
		execute_ast(node->left, data);
		exit(1);
	}
	wait(NULL);
	close(data->fd_file2);
	return (0);
}
