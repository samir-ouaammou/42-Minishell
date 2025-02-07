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
		data.input = ft_strdup(shell.input);
		ft_parsing(&shell);
		if (shell.free == -1 && (!shell.tokens || !shell.three))
			write(2, "minishell: syntax error\n", 24);
		if (shell.input)
		{
			if (shell.three)
				exaction(shell.three, &data, env);
			add_history(shell.input);
			ft_free_parsing(&shell);
		}
		if (data.input)
			free(data.input);
	}
	rl_clear_history();
	(void)av;
	return (0);
}
