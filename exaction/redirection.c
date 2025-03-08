/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahaded <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:34:36 by aahaded           #+#    #+#             */
/*   Updated: 2025/03/07 16:34:38 by aahaded          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_redirection_utils(t_ast *root, int *i, int *fd_in)
{
	(*i)++;
	*fd_in = open(root->right->value[(*i)], O_RDONLY);
	if (*fd_in == -1)
	{
		ft_printf("minishell: %s: %s\n", root->right->value[(*i)],
			strerror(errno));
		return (1);
	}
	return (0);
}

int	handle_redirection_utils2(t_ast *root, int *i, int *fd_out)
{
	(*i)++;
	*fd_out = open(root->right->value[(*i)], O_WRONLY | O_CREAT | O_APPEND,
			0644);
	if (*fd_out == -1)
	{
		ft_printf("minishell: %s: %s\n", root->right->value[(*i)],
			strerror(errno));
		return (1);
	}
	return (0);
}

int	handle_redirection(t_ast *root, int *i, int *fd_out, int *fd_in)
{
	if (ft_strcmp(root->right->value[(*i)], ">") == 0)
	{
		(*i)++;
		*fd_out = open(root->right->value[(*i)], O_WRONLY | O_CREAT | O_TRUNC,
				0644);
		if (*fd_out == -1)
		{
			ft_printf("minishell: %s: %s\n", root->right->value[(*i)],
				strerror(errno));
			return (1);
		}
	}
	else if (ft_strcmp(root->right->value[(*i)], ">>") == 0)
		return (handle_redirection_utils2(root, i, fd_out));
	else if (ft_strcmp(root->right->value[(*i)], "<") == 0)
		return (handle_redirection_utils(root, i, fd_in));
	return (0);
}

int	setup_redirections(t_ast *root, t_exaction *data, int fd_out, int fd_in)
{
	int	stdin_backup;
	int	stdout_backup;

	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	if (fd_out != -1)
		dup2(fd_out, STDOUT_FILENO);
	if (fd_in != -1)
		dup2(fd_in, STDIN_FILENO);
	data->status = execute_ast(root->left, data);
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdin_backup);
	close(stdout_backup);
	if (fd_out != -1)
		close(fd_out);
	if (fd_in != -1)
		close(fd_in);
	return (data->status);
}

int	execute_redirection(t_ast *root, t_exaction *data)
{
	int	i;
	int	fd_out;
	int	fd_in;

	i = 0;
	fd_out = -1;
	fd_in = -1;
	if (!root)
		return (0);
	if (handle_file_redirection(root, &fd_in, &fd_out))
	{
		data_struc()->exit_status = 1;
		return (1);
	}
	while (root->right->value[i])
	{
		if (handle_redirection(root, &i, &fd_out, &fd_in))
		{
			data_struc()->exit_status = 1;
			return (1);
		}
		i++;
	}
	return (setup_redirections(root, data, fd_out, fd_in));
}
