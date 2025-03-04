/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_pipes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaammo <souaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 08:35:04 by aahaded           #+#    #+#             */
/*   Updated: 2025/03/03 13:53:40 by souaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int create_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
		return (FAILED);
	return (SUCCESS);
}

static void execute_child_first(t_ast *node, t_exaction *data, int *pipefd)
{
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	execute_ast(node->left, data);
	ft_exit(data->exit_status);
}

static void execute_child_second(t_ast *node, t_exaction *data, int *pipefd)
{
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	execute_ast(node->right, data);
	ft_exit(data->exit_status);
}

int execute_pipe(t_ast *node, t_exaction *data)
{
	int pipefd[2];

	int(status1), (status2);
	pid_t(pid1), (pid2);
	if (create_pipe(pipefd) == FAILED)
		return (FAILED);
	pid1 = fork();
	if (pid1 == -1)
		return (FAILED);
	if (pid1 == 0)
		execute_child_first(node, data, pipefd);
	pid2 = fork();
	if (pid2 == -1)
		return (FAILED);
	if (pid2 == 0)
		execute_child_second(node, data, pipefd);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	if (WIFEXITED(status2))
	{
		data->exit_status = WEXITSTATUS(status2);
		if (data->exit_status == 127 || data->exit_status == 1)
			data->status = 1;
		// ft_printf("status: %d\n", data->exit_status);
	}
	return (SUCCESS);
}
