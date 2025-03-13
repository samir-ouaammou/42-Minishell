/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaammo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 01:02:43 by souaammo          #+#    #+#             */
/*   Updated: 2025/03/08 01:02:44 by souaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

int	handle_child_exit_status(int status)
{
	int	fd;

	fd = 0;
	if (WIFEXITED(status))
	{
		fd = WEXITSTATUS(status);
		if (fd == 130)
		{
			data_struc()->exit_status = 130;
			data_struc()->bol = 1;
			return (1);
		}
	}
	return (0);
}

int	handle_forked_process(t_parsing *shell, int dolar, t_exaction *data)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		return (1);
	}
	else if (pid == 0)
	{
		signal(SIGINT, sigint_handler);
		ft_read_and_process_heredoc_input(shell, dolar, data);
		close(shell->fd);
		ft_exit(0);
	}
	waitpid(pid, &status, 0);
	return (handle_child_exit_status(status));
}
