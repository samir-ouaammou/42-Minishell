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

int open_file(char *path_name, char *type, t_data *data)
{
	int fd_file;

	path_name = process_strings(path_name, data);
	
	// ft_printf("path_name: {%s}\n", path_name);
	// else if (type == NULL)
	// 	fd_file = open(data->name_path_file2, O_RDONLY);
	// int i = 0;
	// ft_printf("path_name: %s\n", path_name);
	// while (path_name[i])
	// {
	// 	if (path_name[i] == ' ')
	// 		return (42);
	// 	i++;
	// }
	if (ft_strcmp(type, "RightArrow") == 0)
		fd_file = open(path_name, O_WRONLY | O_CREAT | O_APPEND,
					   0644);
	else if (ft_strcmp(type, "redirout") == 0)
		fd_file = open(path_name, O_WRONLY | O_CREAT | O_TRUNC,
					   0644);
	else
		fd_file = -1;
	if (fd_file == -1)
	{
		ft_printf("awd\n");
		ft_printf("minishellawdawd: %s: %s\n", path_name, strerror(errno));
		data->exit_status = 1;
	}
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

// int check_and_open_file(t_ast *node, t_data *data, char *type)
// {
// 	if (!node || !node->right || !node->right->value[0])
// 		return (0);
// 	int fd = check_and_open_file(node->left, data, type);
// 	if (fd == 1)
// 		return (1);
// 	char *str = process_strings(node->right->value[0], data);
// 	if (!str)
// 		return (0);
// 	int i = 0;
// 	// ft_printf("str_1: %s\n", str);
// 	// ft_printf("str_2: %s\n", node->right->value[0]);
// 	while (str[i])
// 	{
// 		if (str[i] == ' ' && ft_strncmp(node->right->value[0], "$", 1) == 0)
// 		{
// 			data->num_proess = 1;
// 			break;
// 		}
// 		i++;
// 	}
// 	free(str);
// 	if (data->num_proess == 0)
// 	{
// 		ft_remove_quots(node->right->value, data);
// 		int d = open_file(node->right->value[0], type, data);
// 		if (d == -1)
// 			return (1);
// 	}
// 	return (0);
// }

int execute_redir_RightArrow_redirout(t_ast *node, t_data *data, char *type)
{
	// if (!node || !node->left || !node->right)
	// 	return (FAILED);
	// if (!node->left->value || !node->right->value)
	// 	return (FAILED);
	// if (!node->right->value[0])
	// 	return (FAILED);
	
	// int fd = check_and_open_file(node, data, type);
	// if (fd == 1)
	// 	return (1);
	// if (data->num_proess == 1)
	// {
	// 	ft_printf("minishell: %s: ambiguous redirect\n", node->right->value[0]);
	// 	data->exit_status = 1;
	// 	return (1);
	// }
	if (data->check_file_1 == 0)
	{
		
		data->name_path_file = ft_strdup(node->right->value[0]);
		if (!data->name_path_file)
		{
			ft_printf("minishell: memory allocation failed\n");
			return (FAILED);
		}
	}
	data->fd_file = open_file(data->name_path_file, type, data);
	if (data->fd_file == -1)
		return (FAILED);
	// if (data->check_file_1 != 0)
	// {
	// 	int d = open_file(node->right->value[0], type, data);
	// 	if (d == -1)
	// 		return (FAILED);
	// }
	// data->check_file_1 = 1;
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