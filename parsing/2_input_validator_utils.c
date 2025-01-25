#include "../libft/libft.h"
#include "Minishell.h"

int	ft_is_redirections(t_parsing *shell, int index)
{
	if (!shell->tokens[index])
		return (0);
	if (!ft_strcmp(shell->tokens[index], "<")
		|| !ft_strcmp(shell->tokens[index], ">")
		|| !ft_strcmp(shell->tokens[index], ">>")
		|| !ft_strcmp(shell->tokens[index], "<<"))
		return (1);
	return (0);
}

int	ft_is_logical_operators(t_parsing *shell, int index)
{
	if (!shell->tokens[index])
		return (0);
	if (!ft_strcmp(shell->tokens[index], "|")
		|| !ft_strcmp(shell->tokens[index], "&")
		|| !ft_strcmp(shell->tokens[index], "||")
		|| !ft_strcmp(shell->tokens[index], "&&"))
		return (1);
	return (0);
}

void	ft_remainder_of_this_function(t_parsing *shell)
{
	if ((!ft_strcmp(shell->tokens[shell->i], "(")
			&& (ft_is_logical_operators(shell, shell->i + 1)))
		|| (!ft_strcmp(shell->tokens[shell->i + 1], ")")
			&& (ft_is_logical_operators(shell, shell->i)
				|| ft_is_redirections(shell, shell->i)))
		|| (!ft_strcmp(shell->tokens[shell->i], "(")
			&& !ft_strcmp(shell->tokens[shell->i + 1], ")"))
		|| (!ft_strcmp(shell->tokens[shell->i + 1], "|")
			&& (ft_is_logical_operators(shell, shell->i)
				|| ft_is_redirections(shell, shell->i))))
		ft_free_all(shell);
}

void	ft_check_operator_position(t_parsing *shell)
{
	if (shell->free == -1 ||!shell->tokens || !shell->tokens[0])
		return ;
	shell->i = 0;
	while (shell->tokens && shell->tokens[shell->i])
	{
		if ((shell->i == 0 && ft_is_logical_operators(shell, 0))
			|| ((!shell->tokens[shell->i + 1]
					&& (ft_is_logical_operators(shell, shell->i)
						|| ft_is_redirections(shell, shell->i))))
			|| (ft_is_logical_operators(shell, shell->i))
			&& (ft_is_logical_operators(shell, shell->i + 1))
			|| (ft_is_redirections(shell, shell->i))
			&& (ft_is_redirections(shell, shell->i + 1))
			|| (!ft_strcmp(shell->tokens[shell->i], "&")))
		{
			ft_free_all(shell);
			return ;
		}
		else if (shell->tokens[shell->i] && shell->tokens[shell->i + 1])
			ft_remainder_of_this_function(shell);
		shell->i++;
	}
}
