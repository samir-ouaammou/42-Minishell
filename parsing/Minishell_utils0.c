#include "../libft/libft.h"
#include "Minishell.h"

void	ft_free_all(t_parsing *shell)
{
	write(1, "Error\n", 6);
	shell->free = 1337;
	shell->bol = -1;
	if (shell->cmds)
		free(shell->cmds);
	if (shell->cmds_split)
	{
		shell->i = 0;
		while (shell->cmds_split[shell->i])
		{
			free(shell->cmds_split[shell->i]);
			shell->cmds_split[shell->i] = NULL;
			shell->i++;
		}
		free(shell->cmds_split);
		shell->cmds_split = NULL;
	}
}

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

void	ft_delete_commits(t_parsing *shell)
{
	if (!shell->input || !shell->input[0])
		return ;
	shell->i = 0;
	while (shell->input[shell->i])
	{
		if (shell->input[shell->i] == '#')
			break ;
		shell->i++;
	}
	if (shell->input[shell->i] == '#')
	{
		while (shell->input[shell->i])
		{
			shell->input[shell->i] = ' ';
			shell->i++;
		}
	}
}

void	ft_parsing(t_parsing *shell)
{
	ft_init_parsing(shell);
	ft_delete_commits(shell);
	ft_check_syntax_errors(shell);
	if (shell->free == 1337 || shell->parentheses != 0)
	{
		ft_free_all(shell);
		return ;
	}
	shell->cmds = malloc(shell->len + 1);
	if (!shell->cmds)
		return ;
	shell->len = 0;
	shell->bol = 1337;
	ft_check_syntax_errors(shell);
	ft_check_remaining_errors(shell);
	ft_parentheses(shell);
	if (shell->free == 1337)
		return ;
	shell->cmds_split = ft_split(shell->cmds, '\n');
}

// // *************** main test **********

// int	main(int ac, char **av)
// {
// 	t_parsing	shell;

// 	if (ac != 1)
// 	{
// 		write(2, "Error: Invalid number of arguments.\n", 36);
// 		exit(-1);
// 	}
// 	while (1)
// 	{
// 		shell.input = readline
//("\033[0;92m➜\033[0;39m\033[1m\033[96m  Minishell\033[0;39m ");
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
// 		// ft_free_all(&shell);
// 	}
// 	rl_clear_history();
// 	(void)av;
// 	return (0);
// }
