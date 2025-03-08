/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahaded <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:35:58 by aahaded           #+#    #+#             */
/*   Updated: 2025/03/07 16:35:59 by aahaded          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_file_redirection_utils(t_ast *root, int *fd_out)
{
	*fd_out = open(root->right->value[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*fd_out == -1)
	{
		ft_printf("minishell: %s: %s\n", root->right->value[0],
			strerror(errno));
		return (1);
	}
	return (0);
}

int	handle_file_redirection(t_ast *root, int *fd_in, int *fd_out)
{
	if (ft_strcmp(root->value[0], ">") == 0)
	{
		*fd_out = open(root->right->value[0], O_WRONLY | O_CREAT | O_TRUNC,
				0644);
		if (*fd_out == -1)
		{
			ft_printf("minishell: %s: %s\n", root->right->value[0],
				strerror(errno));
			return (1);
		}
	}
	else if (ft_strcmp(root->value[0], "<") == 0)
	{
		*fd_in = open(root->right->value[0], O_RDONLY);
		if (*fd_in == -1)
		{
			ft_printf("minishell: %s: %s\n", root->right->value[0],
				strerror(errno));
			return (1);
		}
	}
	else if (ft_strcmp(root->value[0], ">>") == 0)
		return (handle_file_redirection_utils(root, fd_out));
	return (0);
}
