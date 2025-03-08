/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahaded <aahaded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 08:22:07 by aahaded           #+#    #+#             */
/*   Updated: 2025/03/03 13:53:40 by aahaded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_is_directory(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[0] == '/')
			return (1);
		else if (str[i] == '.' && str[i + 1] == '/')
			return (1);
		i++;
	}
	return (0);
}

void	process_command_in_child(t_exaction *data, char **cmd)
{
	char	*path_args;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (check_is_directory(cmd[0]) == 1)
		is_directory(cmd[0]);
	path_args = get_path_env(cmd[0], data);
	if ((path_args && !contains_slash(cmd[0])))
	{
		if (execve(path_args, cmd, data->env) == -1)
			ft_printf("minishell: %s: %s\n", cmd[0], strerror(errno));
	}
	else if (!path_args && contains_slash(cmd[0]))
		handle_execve_error(cmd, data);
	else
		handle_exec_failure(cmd[0], contains_slash(cmd[0]));
	ft_exit(0);
}

int	handle_process_exit(int status)
{
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

int	execute_command(char **cmd, t_exaction *data)
{
	pid_t	pid;
	int		status;

	if (cmd[0][0] == '\0' || (cmd[0][0] == '.' && cmd[0][1] == '\0'))
	{
		ft_printf("minishell: %s: Command not found\n", cmd[0]);
		data_struc()->exit_status = 127;
		return (FAILED);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		data_struc()->exit_status = 1;
		return (FAILED);
	}
	if (pid == 0)
		process_command_in_child(data, cmd);
	waitpid(pid, &status, 0);
	return (handle_process_exit(status));
}
