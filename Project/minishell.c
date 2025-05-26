/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahaded <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 00:15:14 by aahaded           #+#    #+#             */
/*   Updated: 2025/03/08 00:15:15 by aahaded          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	ft_init_parsing(t_parsing *shell)
{
	shell->i = 0;
	shell->j = 0;
	shell->bol = 0;
	shell->len = 0;
	shell->end = 0;
	shell->fd = -1;
	shell->free = 0;
	shell->start = 0;
	shell->parent = 0;
	shell->brackets = 0;
	shell->priority = 0;
	shell->cmds = NULL;
	shell->name = NULL;
	shell->itoa = NULL;
	shell->stop = NULL;
	shell->line = NULL;
	shell->help = NULL;
	shell->temp = NULL;
	shell->tree = NULL;
	shell->tokens = NULL;
	shell->lst_help1 = NULL;
	shell->lst_help2 = NULL;
	shell->start_node = NULL;
	shell->end_node = NULL;
}

void	ft_init_exaction(t_exaction *exec)
{
	exec->matches = NULL;
	exec->env = NULL;
	exec->export = NULL;
	exec->copy = NULL;
	exec->save_oldpwd = NULL;
	exec->status = 0;
	exec->exit_status = 0;
	exec->name_pro = NULL;
	exec->count_ok = 0;
	exec->is_plus = 0;
	exec->save_pwd = NULL;
	exec->bol = 0;
	exec->is_foreground = 1;
	exec->space = 0;
}

void	get_shell_context(t_parsing shell, t_exaction *data)
{
	data_struc()->is_foreground = 1;
	shell.input = readline(data->name_pro);
	data_struc()->is_foreground = 0;
	if (!shell.input)
	{
		ft_printf("exit\n");
		ft_exit(data_struc()->exit_status);
	}
	shell.history = ft_strdup(shell.input);
	ft_parsing(&shell, 0, data);
	if (shell.free == -1)
		write(2, "minishell: syntax error\n", 24);
	if (shell.input && shell.tree && data_struc()->bol == 0 && shell.free != -1)
		exaction(shell.tree, data);
	if (shell.history)
	{
		add_history(shell.history);
		shell.history = NULL;
	}
	data_struc()->bol = 0;
}

int	main(int ac, char **av, char **env)
{
	t_parsing	shell;
	t_exaction	data;

	if (ac != 1)
	{
		write(2, "Error: Invalid number of arguments.\n", 36);
		ft_exit(-1);
	}
	ft_init_parsing(&shell);
	ft_init_exaction(&data);
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	read_env(env, &data);
	data.name_pro = "➜ Minishell ";
	while (1)
		get_shell_context(shell, &data);
	rl_clear_history();
	(void)av;
	return (0);
}
