#include "./minishell.h"

int	main(int ac, char **av, char **env)
{
	t_parsing	shell;
	t_data		data;

	if (ac != 1)
	{
		write(2, "Error: Invalid number of arguments.\n", 36);
		exit(-1);
	}
	memset(&data, 0, sizeof(t_data)); //	?? mem => ft_mem
	read_env(&data, env);
	data.name_pro = "➜ Minishell ";
	while (1)
	{
		shell.input = readline(data.name_pro);
		shell.history = ft_strdup(shell.input);
		ft_parsing(&shell, 0);
		if (shell.free == -1 && (!shell.tokens || !shell.tree))
			write(2, "minishell: syntax error\n", 24);
		if (shell.input)
		{
			printf("input =>   [%s]\n\n", shell.input);
			if (shell.tree)
				exaction(shell.tree, &data);
			add_history(shell.history);
			ft_free_parsing(&shell);
		}
		if (shell.history)
		{
			free(shell.history);
			shell.history = NULL;
		}
	}
	rl_clear_history();
	(void)av;
	return (0);
}
