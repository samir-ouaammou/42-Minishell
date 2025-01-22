#include "../libft/libft.h"
#include "Minishell.h"

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
	if (!ft_strcmp(shell->cmds_split[index], "|")
		|| !ft_strcmp(shell->cmds_split[index], "&")
		|| !ft_strcmp(shell->cmds_split[index], "||")
		|| !ft_strcmp(shell->cmds_split[index], "&&"))
		return (1);
	return (0);
}

void	ft_remainder_of_this_function(t_parsing *shell)
{
	if ((!ft_strcmp(shell->cmds_split[shell->i], "(")
			&& (ft_is_logical_operators(shell, shell->i + 1)))
		|| (!ft_strcmp(shell->cmds_split[shell->i + 1], ")")
			&& (ft_is_logical_operators(shell, shell->i)
				|| ft_is_redirections(shell, shell->i)))
		|| (!ft_strcmp(shell->cmds_split[shell->i], "(")
			&& !ft_strcmp(shell->cmds_split[shell->i + 1], ")"))
		|| (!ft_strcmp(shell->cmds_split[shell->i + 1], "|")
			&& (ft_is_logical_operators(shell, shell->i)
				|| ft_is_redirections(shell, shell->i))))
		ft_free_all(shell);
}

void	ft_check_operator_position(t_parsing *shell)
{
	if (shell->free == -1 ||!shell->cmds_split || !shell->cmds_split[0])
		return ;
	shell->i = 0;
	while (shell->cmds_split && shell->cmds_split[shell->i])
	{
		if ((shell->i == 0 && ft_is_logical_operators(shell, 0))
			|| ((!shell->cmds_split[shell->i + 1]
					&& (ft_is_logical_operators(shell, shell->i)
						|| ft_is_redirections(shell, shell->i))))
			|| (ft_is_logical_operators(shell, shell->i))
			&& (ft_is_logical_operators(shell, shell->i + 1))
			|| (ft_is_redirections(shell, shell->i))
			&& (ft_is_redirections(shell, shell->i + 1))
			|| (!ft_strcmp(shell->cmds_split[shell->i], "&")))
		{
			ft_free_all(shell);
			return ;
		}
		else if (shell->cmds_split[shell->i] && shell->cmds_split[shell->i + 1])
			ft_remainder_of_this_function(shell);
		shell->i++;
	}
}
