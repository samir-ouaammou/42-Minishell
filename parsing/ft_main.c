#include "../libft/libft.h"
#include "Minishell.h"

void	ft_init_parsing(t_parsing *shell)
{
	shell->i = 0;
	shell->j = 0;
	shell->len = 0;
	shell->bol = 0;
	shell->free = 0;
	shell->parentheses = 0;
	shell->cmds = NULL;
	shell->cmds_split = NULL;
}

void	ft_free_all(t_parsing *shell)
{
	if (shell->free == -1)
		return ;
	write(2, "Minishell: syntax error\n", 24);
	shell->free = -1;
	if (shell->cmds != NULL)
		free(shell->cmds);
	if (shell->cmds_split)
	{
		shell->i = 0;
		while (shell->cmds_split[shell->i])
		{
			if (shell->cmds_split[shell->i] != NULL)
			{
				free(shell->cmds_split[shell->i]);
				shell->cmds_split[shell->i] = NULL;
			}
			shell->i++;
		}
		free(shell->cmds_split);
		shell->cmds_split = NULL;
	}
}

void	ft_parsing(t_parsing *shell)
{
	ft_init_parsing(shell);
	ft_split_args(shell);
	ft_check_syntax_errors(shell);
}

// // *************** main test **********

// int	main(int ac, char **av)
// {
// 	t_parsing shell;

// 	if (ac != 1)
// 	{
// 		write(2, "Error: Invalid number of arguments.\n", 36);
// 		exit(-1);
// 	}
// 	while (1)
// 	{
// 		shell.input = readline("➜ Minishell ");
// 		ft_parsing(&shell);
// 		shell.i = 0;
// 		if (shell.cmds_split)
// 		{
// 			while (shell.cmds_split[shell.i])
// 			{
// 				printf("%d ==> %s\n", shell.i, shell.cmds_split[shell.i]);
// 				shell.i++;
// 			}
// 		}
// 		//  ft_execution("tsna");
// 		add_history(shell.input);
// 		free(shell.input);
// 		// if (shell.free != -1)
// 		// 	ft_free_all(&shell);
// 	}
// 	rl_clear_history();
// 	(void)av;
// 	return (0);
// }