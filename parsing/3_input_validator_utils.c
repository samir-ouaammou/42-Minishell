
#include "../minishell.h"

int	ft_is_redirections(t_parsing *shell, int index)
{
	if (!shell->temp[index])
		return (0);
	if (!ft_strcmp(shell->temp[index], "<")
		|| !ft_strcmp(shell->temp[index], ">")
		|| !ft_strcmp(shell->temp[index], ">>")
		|| !ft_strcmp(shell->temp[index], "<<"))
		return (1);
	return (0);
}

int	ft_is_logical_operators(t_parsing *shell, int index)
{
	if (!shell->temp[index])
		return (0);
	if (!ft_strcmp(shell->temp[index], "|")
		|| !ft_strcmp(shell->temp[index], "&")
		|| !ft_strcmp(shell->temp[index], "||")
		|| !ft_strcmp(shell->temp[index], "&&"))
		return (1);
	return (0);
}

void	ft_remainder_of_this_function(t_parsing *shell)
{
	if ((!ft_strcmp(shell->temp[shell->i], "(")
			&& (ft_is_logical_operators(shell, shell->i + 1)))
		|| (!ft_strcmp(shell->temp[shell->i + 1], ")")
			&& (ft_is_logical_operators(shell, shell->i)
				|| ft_is_redirections(shell, shell->i)))
		|| (!ft_strcmp(shell->temp[shell->i], "(")
			&& !ft_strcmp(shell->temp[shell->i + 1], ")"))
		|| (!ft_strcmp(shell->temp[shell->i + 1], "|")
			&& (ft_is_logical_operators(shell, shell->i)
				|| ft_is_redirections(shell, shell->i))))
		ft_free_args(shell);
}

void	ft_check_operator_position(t_parsing *shell)
{
	if (shell->free == -1 ||!shell->temp || !shell->temp[0])
		return ;
	shell->i = 0;
	while (shell->temp && shell->temp[shell->i])
	{
		if ((shell->i == 0 && ft_is_logical_operators(shell, 0))
			|| (!shell->temp[shell->i + 1]
				&& (ft_is_logical_operators(shell, shell->i)
					|| ft_is_redirections(shell, shell->i)))
			|| ((ft_is_logical_operators(shell, shell->i))
				&& (ft_is_logical_operators(shell, shell->i + 1)))
			|| ((ft_is_redirections(shell, shell->i))
				&& (ft_is_redirections(shell, shell->i + 1)))
			|| (!ft_strcmp(shell->temp[shell->i], "&")))
		{
			ft_free_args(shell);
			return ;
		}
		else if (shell->temp[shell->i] && shell->temp[shell->i + 1])
			ft_remainder_of_this_function(shell);
		shell->i++;
	}
}
