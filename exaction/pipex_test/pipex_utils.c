/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahaded <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 21:11:01 by aahaded           #+#    #+#             */
/*   Updated: 2024/12/07 18:22:24 by aahaded          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

void	check_args(int argc, char **env)
{
	if (argc != 5)
	{
		ft_putstr_fd("Error: Bad arguments\n", 2);
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2\n", 2);
		exit(EXIT_FAILURE);
	}
	if (!*env)
	{
		ft_putstr_fd("Error: environment\n", 2);
		exit(EXIT_FAILURE);
	}
}

void	pipe_fork_tcheck_err(pid_t pid, int pipen)
{
	if (pipen < 0)
	{
		perror("Error: pipe");
		exit(EXIT_FAILURE);
	}
	if (pid < 0)
	{
		perror("Error: fork");
		exit(EXIT_FAILURE);
	}
}
