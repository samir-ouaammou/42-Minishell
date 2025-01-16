/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahaded <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:15:34 by aahaded           #+#    #+#             */
/*   Updated: 2024/12/07 21:26:48 by aahaded          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex_bonus.h"

void	execute_command(char *cmd, char **env)
{
	char	**words;

	words = ft_split(cmd, ' ');
	execve(get_path_env(words[0], env), words, NULL);
	perror("Error executing command");
	exit(EXIT_FAILURE);
}

static void	setup_pipeline_fork_(int argc, char **argv, char **env)
{
	int	file2;

	file2 = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file2 < 0)
	{
		perror("Error opening file2");
		exit(EXIT_FAILURE);
	}
	dup2(file2, STDOUT_FILENO);
	close(file2);
	execute_command(argv[argc - 2], env);
}

void	setup_pipeline_fork(int argc, char **argv, int i, char **env)
{
	int		pipefd[2];
	pid_t	pid;
	int		pipen;

	while (i < argc - 2)
	{
		pipen = pipe(pipefd);
		pid = fork();
		pipe_fork_tcheck_err(pid, pipen);
		if (pid == 0)
		{
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
		}
		else
		{
			close(pipefd[0]);
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[1]);
			execute_command(argv[i], env);
		}
		i++;
	}
	setup_pipeline_fork_(argc, argv, env);
}
