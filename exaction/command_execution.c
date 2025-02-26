/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahaded <aahaded@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 08:22:07 by aahaded           #+#    #+#             */
/*   Updated: 2025/02/17 08:22:09 by aahaded          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int is_directory(char *cmd)
{
	struct stat statbuf;

	if (stat(cmd, &statbuf) == 0 && S_ISDIR(statbuf.st_mode))
	{
		fprintf(stderr, "minishell: %s: Is a directory\n", cmd);
		exit(126);
	}
	return (0);
}

static int contains_slash(char *cmd)
{
	int i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

static void handle_exec_failure(char *cmd, int check_, char *path_args)
{
	(void)path_args;
	if (check_)
	{
		ft_printf("minishell: %s: No such file or directory\n", cmd);
		// free(path_args);
		exit(127);
	}
	ft_printf("minishell: %s: Command not found\n", cmd);
	// free(path_args);
	exit(127);
}

static int handle_exit_status(t_data *data, int status)
{
	if (WEXITSTATUS(status) == 0)
	{
		data->exit_status = 0;
		return (SUCCESS);
	}
	else if (WEXITSTATUS(status) == 126)
	{
		data->exit_status = 126;
		return (FAILED);
	}
	else if (WEXITSTATUS(status) == 127)
	{
		data->exit_status = 127;
		return (FAILED);
	}
	else
		data->exit_status = 1;
	return (FAILED);
}

int execute_command(char **cmd, t_data *data)
{
	pid_t pid;
	int status, exit_s;

	if (cmd[0][0] == '\0')
	{
		ft_printf("minishell: %s: Command not found\n", cmd[0]);
		data->exit_status = 127;
		return (1);
	}
	pid = fork();
	if (pid == -1)
		return (FAILED);
	if (pid == 0)
	{
		is_directory(cmd[0]);
		char *path_args = get_path_env(cmd[0], data);
		if ((path_args != NULL && !contains_slash(cmd[0])) || cmd[0][0] == '.')
		{
			if (!path_args)
				path_args = ft_strdup(cmd[0]);
			execve(path_args, cmd, data->env);
		}
		else
			handle_exec_failure(cmd[0], contains_slash(cmd[0]), path_args);
		return (FAILED);
	}
	wait(&status);
	if (WIFEXITED(status))
	{
		exit_s = handle_exit_status(data, status);
		if (exit_s == FAILED)
			return (FAILED);
		else if (exit_s == SUCCESS)
			return (SUCCESS);
	}
	return (FAILED);
}