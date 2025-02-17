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


//------------------------------------------------------

//------------------------------------------------------
static int	open_file(t_ast *node, char *type)
{
	int	fd_file;

	if (ft_strcmp(type, "RightArrow") == 0)
		fd_file = open(node->right->value[0], O_WRONLY | O_CREAT | O_APPEND,
				0644);
	else if (ft_strcmp(type, "redirout") == 0)
		fd_file = open(node->right->value[0], O_WRONLY | O_CREAT | O_TRUNC,
				0644);
	else
		fd_file = -1;
	if (fd_file == -1)
		perror("Error");
	return (fd_file);
}

static char	**create_args_without_left(t_ast *node)
{
	char	**res;

	int(i), (j), (count_right);
	i = 1;
	count_right = count_args_value(node, "right");
	res = malloc(sizeof(char *) * (count_right + 1));
	if (!res)
		return (NULL);
	i = 1;
	j = 0;
	while (j < count_right)
	{
		res[j] = ft_strdup(node->right->value[i]);
		j++;
		i++;
	}
	res[i] = NULL;
	return (res);
}

static char	**create_args_with_left(t_ast *node)
{
	char	**res;

	int(i), (count_left), (count_right);
	i = 1;
	count_left = count_args_value(node, "left");
	count_right = count_args_value(node, "right");
	res = malloc(sizeof(char *) * (count_left + count_right + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i < count_left)
	{
		res[i] = ft_strdup(node->left->value[i]);
		if (!res[i])
			return (NULL);
		i++;
	}
	i = 1;
	while (node->right->value[i])
	{
		res[i + count_left - 1] = ft_strdup(node->right->value[i]);
		i++;
	}
	res[count_left + count_right] = NULL;
	return (res);
}

void	execute_redir_RightArrow_redirout(t_ast *node, t_data *data, char *type)
{
	char	**res;

	int(fd_file), (stdout_backup);
	fd_file = open_file(node, type);
	if (fd_file == -1)
		return ;
	stdout_backup = dup(STDOUT_FILENO);
	dup2(fd_file, STDOUT_FILENO);
	close(fd_file);
	if (!node->left)
	{
		res = create_args_without_left(node);
		if (!res)
			return ;
		data->status = execute_command(res, data);
	}
	else
	{
		res = create_args_with_left(node);
		if (!res)
			return ;
		node->left->value = res;
		execute_ast(node->left, data);
	}
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdout_backup);
}
