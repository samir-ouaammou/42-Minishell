#include "../minishell.h"

void	ft_free_parsing(t_parsing *shell)
{
	if (shell->free != -1)
		ft_free_args(shell);
}

void	ft_free_args(t_parsing *shell)
{
	if (!shell || shell->free == -1)
		return ;
	shell->free = -1;
}
