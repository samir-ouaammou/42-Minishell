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

// static int count_args_value(t_ast *node, char *type)
// {
// 	int count;

// 	count = 0;
// 	if (ft_strcmp(type, "left") == 0)
// 	{
// 		while (node->left->value[count])
// 			count++;
// 	}
// 	else if (ft_strcmp(type, "right") == 0)
// 	{
// 		while (node->right->value[count])
// 			count++;
// 	}
// 	return (count);
// }

static int open_file(char *path_name, char *type)
{
	int fd_file;

	if (ft_strcmp(type, "RightArrow") == 0)
		fd_file = open(path_name, O_WRONLY | O_CREAT | O_APPEND,
					   0644);
	else if (ft_strcmp(type, "redirout") == 0)
		fd_file = open(path_name, O_WRONLY | O_CREAT | O_TRUNC,
					   0644);
	else
		fd_file = -1;
	if (fd_file == -1)
		ft_printf("minishell: %s: %s\n", path_name, strerror(errno));
	return (fd_file);
}

// static char **create_args_without_left(t_ast *node)
// {
// 	char **res;

// 	int(i), (j), (count_right);
// 	i = 1;
// 	count_right = count_args_value(node, "right");
// 	res = malloc(sizeof(char *) * (count_right + 1));
// 	if (!res)
// 		return (NULL);
// 	i = 1;
// 	j = 0;
// 	while (j < count_right)
// 	{
// 		if (i >= count_right)
// 			break ;
// 		res[j] = ft_strdup(node->right->value[i]);
// 		j++;
// 		i++;
// 	}
// 	res[i] = NULL;
// 	return (res);
// }

// static char **create_args_with_left(t_ast *node)
// {
// 	char **res;

// 	int(i), (count_left), (count_right);
// 	i = 1;
// 	count_left = count_args_value(node, "left");
// 	count_right = count_args_value(node, "right");
// 	res = malloc(sizeof(char *) * (count_left + count_right + 1));
// 	if (!res)
// 		return (NULL);
// 	i = 0;
// 	while (i < count_left)
// 	{
// 		res[i] = ft_strdup(node->left->value[i]);
// 		if (!res[i])
// 			return (NULL);
// 		i++;
// 	}
// 	i = 1;
// 	while (node->right->value[i])
// 	{
// 		res[i + count_left - 1] = ft_strdup(node->right->value[i]);
// 		i++;
// 	}
// 	res[count_left + count_right] = NULL;
// 	return (res);
// }

int execute_redir_RightArrow_redirout(t_ast *node, t_data *data, char *type)
{
	(void)type;

	// if (!node || !node->left || !node->right)
	// 	return (FAILED);
	// if (!node->left->value || !node->right->value)
	// 	return (FAILED);
	// if (!node->right->value[0])
	// 	return (FAILED);
	if (data->check_file_1 == 0)
	{
		if (data->name_path_file)
			free(data->name_path_file);
		data->name_path_file = ft_strdup(node->right->value[0]);
		if (!data->name_path_file)
		{
			ft_printf("minishell: memory allocation failed\n");
			return (FAILED);
		}
	}
	data->check_file_1 = 1;
	data->fd_file = open_file(data->name_path_file, type);
	if (data->fd_file == -1)
		return (FAILED);
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
		execute_ast(node->left, data);
		exit(1);
	}
	wait(NULL);
	close(data->fd_file);
	return (0);
}