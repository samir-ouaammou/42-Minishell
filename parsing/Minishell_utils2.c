#include "../libft/libft.h"
#include "Minishell.h"

void	ft_parentheses(t_parsing *shell)
{
	if (shell->free == 1337)
		return ;
	shell->j = 0;
	while (shell->cmds[shell->j])
	{
		if (shell->cmds[shell->j] == '(')
			shell->parentheses++;
		if (shell->cmds[shell->j] == ')')
			shell->parentheses--;
		if (shell->parentheses < 0)
			break ;
		shell->j++;
	}
	if (shell->parentheses != 0)
		ft_free_all(shell);
	else
	{
		shell->j--;
		while ((shell->j > 0) && (shell->cmds[shell->j] == ' '
				|| shell->cmds[shell->j] == '\n'))
			shell->j--;
		if (shell->cmds[shell->j] == '|' || shell->cmds[shell->j] == '&')
			ft_free_all(shell);
	}
}

int	ft_check_operators(t_parsing *shell)
{
	if ((shell->input[shell->i] == '|' && shell->input[shell->i + 1] == '|')
		|| (shell->input[shell->i] == '&' && shell->input[shell->i + 1] == '&')
		|| (shell->input[shell->i] == '>' && shell->input[shell->i + 1] == '>')
		|| (shell->input[shell->i] == '<' && shell->input[shell->i + 1] == '<'))
		return (1);
	return (0);
}
