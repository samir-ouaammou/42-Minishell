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
				|| shell->cmds[shell->j] == '\t'
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

int	ft_is_redirections(t_parsing *shell, int index)
{
	if (!shell->cmds_split[index])
		return (0);
	if (!ft_strcmp(shell->cmds_split[index], "<")
		|| !ft_strcmp(shell->cmds_split[index], ">")
		|| !ft_strcmp(shell->cmds_split[index], ">>")
		|| !ft_strcmp(shell->cmds_split[index], "<<"))
		return (1);
	return (0);
}

int	ft_is_logical_operators(t_parsing *shell, int index)
{
	if (!shell->cmds_split[index])
		return (0);
	if (!(ft_strcmp(shell->cmds_split[index], "|"))
		|| (!ft_strcmp(shell->cmds_split[index], "||"))
		|| (!ft_strcmp(shell->cmds_split[index], "&&")))
		return (1);
	return (0);
}

void	ft_check_operator_position(t_parsing *shell)
{
	if (!shell->cmds_split || !shell->cmds_split[0])
		return ;
	shell->i = 0;
	while (shell->cmds_split[shell->i])
	{
		if ((shell->i == 0 && (ft_is_logical_operators(shell, 0)
			|| ft_is_redirections(shell, 0))) || ((!shell->cmds_split[shell->i + 1]
			&& (ft_is_logical_operators(shell, shell->i)
			|| ft_is_redirections(shell, shell->i))))
			|| (ft_is_logical_operators(shell, shell->i))
			&& (ft_is_logical_operators(shell, shell->i + 1))
			|| (ft_is_redirections(shell, shell->i))
			&& (ft_is_redirections(shell, shell->i + 1)))
		{
			ft_free_all(shell);
			return ;
		}
		shell->i++;
	}
}
