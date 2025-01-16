/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahaded <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:14:48 by aahaded           #+#    #+#             */
/*   Updated: 2024/12/09 20:07:22 by aahaded          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex_bonus.h"

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

void	ft_read_file1(char **argv)
{
	int	file1;

	file1 = open(argv[1], O_RDONLY);
	if (file1 < 0)
	{
		perror("Error opening file1");
		exit(EXIT_FAILURE);
	}
	dup2(file1, STDIN_FILENO);
	close(file1);
}

void	check_arguments(int argc, char **argv, char **env)
{
	if (argc < 5)
	{
		ft_putstr_fd("Error: Bad arguments\n", 2);
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2\n", 2);
		exit(EXIT_FAILURE);
	}
	if (argc < 6 && (ft_strncmp(argv[1], "here_doc",
				ft_strlen((const char *)argv[1])) == 0 || ft_strncmp(argv[1],
				".here_doc", ft_strlen((const char *)argv[1])) == 0))
	{
		ft_putstr_fd("Error: Bad arguments\n", 2);
		ft_putstr_fd("Usage: ./pipex here_doc LIMITER cmd cmd1 file\n", 2);
		exit(EXIT_FAILURE);
	}
	if (!*env)
	{
		ft_putstr_fd("Error: environment\n", 2);
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv, char **env)
{
	int	i;

	check_arguments(argc, argv, env);
	if (ft_strncmp(argv[1], "here_doc", ft_strlen((const char *)argv[1])) == 0
		|| ft_strncmp(argv[1], ".here_doc",
			ft_strlen((const char *)argv[1])) == 0)
		check_commands_and_here_doc(argc, argv, env);
	else
		ft_read_file1(argv);
	if (ft_strncmp(argv[1], "here_doc", ft_strlen((const char *)argv[1])) == 0
		|| ft_strncmp(argv[1], ".here_doc",
			ft_strlen((const char *)argv[1])) == 0)
		i = 3;
	else
		i = 2;
	setup_pipeline_fork(argc, argv, i, env);
	exit(EXIT_SUCCESS);
}
