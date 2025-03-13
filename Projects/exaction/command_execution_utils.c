/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahaded <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 00:08:58 by aahaded           #+#    #+#             */
/*   Updated: 2025/03/07 00:08:59 by aahaded          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

int	is_directory(char *cmd)
{
	struct stat	statbuf;

	if (stat(cmd, &statbuf) == 0 && S_ISDIR(statbuf.st_mode))
	{
		ft_printf("minishell: %s: Is a directory\n", cmd);
		ft_exit(126);
	}
	return (0);
}

int	contains_slash(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

void	handle_exec_failure(char *cmd, int check_)
{
	if (check_)
	{
		ft_printf("minishell: %s: No such file or directory\n", cmd);
		ft_exit(127);
	}
	ft_printf("minishell: %s: Command not found\n", cmd);
	ft_exit(127);
}

void	handle_execve_error(char **cmd, t_exaction *data)
{
	if (execve(cmd[0], cmd, data->env) == -1)
	{
		if (errno == EACCES)
		{
			ft_printf("minishell: %s: Permission denied\n", cmd[0]);
			ft_exit(126);
		}
		else
			handle_exec_failure(cmd[0], contains_slash(cmd[0]));
	}
}
