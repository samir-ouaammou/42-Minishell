/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahaded <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:46:23 by aahaded           #+#    #+#             */
/*   Updated: 2024/12/09 20:06:25 by aahaded          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

char	*get_path_env_utils(char **path, char *cmd)
{
	char	*path_arg;
	int		i;

	i = 0;
	while (path[i])
	{
		path_arg = ft_strjoin(path[i], "/");
		path_arg = ft_strjoin(path_arg, cmd);
		if (access(path_arg, X_OK) == 0)
			return (path_arg);
		i++;
	}
	return (NULL);
}

char	*get_path_env(char *cmd, char **env)
{
	int		i;
	int		check_path;
	char	**path;

	i = 0;
	check_path = 0;
	path = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			check_path = 1;
			path = ft_split(env[i] + 5, ':');
			break ;
		}
		i++;
	}
	if (!check_path)
		exit(EXIT_FAILURE);
	if (get_path_env_utils(path, cmd))
		return (get_path_env_utils(path, cmd));
	ft_putstr_fd("Error: commad not found", 2);
	return (NULL);
}

void	child_process(char **argv, int *pipefd, char **env)
{
	int		file1;
	char	**words;

	file1 = open(argv[1], O_RDONLY);
	if (file1 == -1)
	{
		perror("Error opening file1");
		exit(EXIT_FAILURE);
	}
	dup2(file1, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(file1);
	close(pipefd[0]);
	close(pipefd[1]);
	words = ft_split(argv[2], ' ');
	execve(get_path_env(words[0], env), words, NULL);
	perror("Error executing cmd1");
	exit(EXIT_FAILURE);
}

void	parent_process(char **argv, int *pipefd, char **env)
{
	int		file2;
	char	**words;

	file2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file2 == -1)
	{
		perror("Error opening file2");
		exit(EXIT_FAILURE);
	}
	dup2(file2, STDOUT_FILENO);
	dup2(pipefd[0], STDIN_FILENO);
	close(file2);
	close(pipefd[0]);
	close(pipefd[1]);
	words = ft_split(argv[3], ' ');
	execve(get_path_env(words[0], env), words, NULL);
	perror("Error executing cmd2");
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv, char **env)
{
	int		pipefd[2];
	pid_t	pid;
	int		pipen;

	check_args(argc, env);
	pipen = pipe(pipefd);
	pid = fork();
	pipe_fork_tcheck_err(pid, pipen);
	if (pid == 0)
		child_process(argv, pipefd, env);
	else
	{
		wait(NULL);
		parent_process(argv, pipefd, env);
	}
	exit(EXIT_SUCCESS);
}
