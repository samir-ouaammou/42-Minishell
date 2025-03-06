/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaammo <souaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 08:22:07 by aahaded           #+#    #+#             */
/*   Updated: 2025/03/03 13:53:40 by souaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int is_directory(char *cmd)
{
	struct stat statbuf;

	if (stat(cmd, &statbuf) == 0 && S_ISDIR(statbuf.st_mode))
	{
		fprintf(stderr, "minishell: %s: Is a directory\n", cmd);
		ft_exit(126);
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
		ft_exit(127);
	}
	fprintf(stderr, "minishell: %s: Command not found\n", cmd);
	ft_exit(127);
}

int execute_command(char **cmd, t_exaction *data)
{
	pid_t pid;
	int status;

	if (cmd[0][0] == '\0')
	{
		ft_printf("minishell: %s: Command not found\n", cmd[0]);
		data_struc()->exit_status = 0;
		return (1);
	}
	pid = fork();
	if (pid == -1)
		return (FAILED);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		is_directory(cmd[0]);
		char *path_args = get_path_env(cmd[0], data);
		if ((path_args != NULL && !contains_slash(cmd[0])))
		{
			if (execve(path_args, cmd, data_struc()->env) == -1)
				ft_printf("minishell: %s: %s\n", cmd[0], strerror(errno));
		}
		else if (!path_args && contains_slash(cmd[0]))
		{
			if (execve(cmd[0], cmd, data_struc()->env) == -1)
			{
				ft_printf("minishell: %s: %s\n", cmd[0], strerror(errno));
				ft_exit(126);
			}
		}
		else
			handle_exec_failure(cmd[0], contains_slash(cmd[0]), path_args);
		ft_exit(0);
	}
	wait(&status);
	if (WIFSIGNALED(status))
	{
		data_struc()->exit_status = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)", STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		return (SUCCESS);
	}
	else
	{
		data_struc()->exit_status = WEXITSTATUS(status);
		if (data_struc()->exit_status == 0)
			return (SUCCESS);
	}
	return (FAILED);
}