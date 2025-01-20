#include "../libft/libft.h"
#include "Minishell.h"

void	ft_check_the_brackets(t_parsing *shell)
{
	if (shell->free == -1)
		return ;
	shell->i = 0;
	while (shell->cmds_split[shell->i])
	{
		shell->j = 0;
		while (shell->cmds_split[shell->i][shell->j])
		{
			if (shell->cmds_split[shell->i][shell->j] == '(')
				shell->parentheses++;
			if (shell->cmds_split[shell->i][shell->j] == ')')
				shell->parentheses--;
			shell->j++;
		}
		if (shell->parentheses < 0)
		{
			ft_free_all(shell);
			return ;
		}
		shell->i++;
	}
	if (shell->parentheses != 0)
		ft_free_all(shell);
}

void	ft_check_syntax_errors(t_parsing *shell)
{
	ft_check_the_brackets(shell);
	ft_check_operator_position(shell);
}
