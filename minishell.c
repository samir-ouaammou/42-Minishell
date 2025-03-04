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

void ft_init_exaction(t_exaction *data)
{
    data->status = 0;
    data->is_plus = 0;
    data->fd_file = -1;
    data->count_ok = 0;
    data->fd_file2 = -1;
    data->check_exe = 0;
    data->check_pipe = 0;
    data->save_index = 0;
    data->exit_status = 0;
    data->check_fmatch = 0;
    data->stdin_backup = -1;
    data->stdout_backup = -1;
    data->check_operator = 0;
    data->check_parenthese = 0;
    data->env = NULL;
    data->input = NULL;
    data->shell = NULL;
    data->export = NULL;
    data->matches = NULL;
    data->save_pwd = NULL;
    data->name_pro = NULL;
    data->env_buffer = NULL;
    data->DollarSign = NULL;
    data->export_buffer = NULL;
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
	read_env(&data, env);
	data.name_pro = "➜ Minishell ";
	while (1)
	{
		shell.input = readline(data.name_pro);
		shell.history = ft_strdup(shell.input);
		ft_parsing(&shell, 0, &data);
		if (shell.free == -1 && (!shell.tokens || !shell.tree))
			write(2, "minishell: syntax error\n", 24);
		if (shell.input)
		{
			if (shell.tree)
				exaction(shell.tree, &data);
			ft_free_parsing(&shell);
		}
		if (shell.history)
		{
			add_history(shell.history);
			// free(shell.history);
			shell.history = NULL;
			if (shell.input)
			{
				free(shell.input);
				shell.input = NULL;
			}
		}
	}
	rl_clear_history();
	(void)av;
	return (0);
}
