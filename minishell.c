#include "./minishell.h"

void ft_init_parsing(t_parsing *shell)
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



int main(int ac, char **av, char **env)
{
	t_parsing shell;
	t_exaction data;

	if (ac != 1)
	{
		write(2, "Error: Invalid number of arguments.\n", 36);
		ft_exit(-1);
	}
	ft_init_parsing(&shell);
	memset(&data, 0, sizeof(t_exaction));
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	read_env(env);
	data.name_pro = "➜ Minishell ";
	while (1)
	{
		data_struc()->is_foreground = 1;
		shell.input = readline(data.name_pro);
		data_struc()->is_foreground = 0;
		if (!shell.input)
		{
			ft_printf("exit\n");
			ft_exit(data.exit_status);
		}
		shell.history = ft_strdup(shell.input);
		ft_parsing(&shell, 0, &data);
		if (shell.free == -1 && (!shell.tokens || !shell.tree))
			write(2, "minishell: syntax error\n", 24);
		if (shell.input && shell.tree && data_struc()->bol == 0)
			exaction(shell.tree, &data);
		if (shell.history)
		{
			add_history(shell.history);
			shell.history = NULL;
		}
		data_struc()->bol = 0;
	}
	rl_clear_history();
	(void)av;
	return (0);
}
