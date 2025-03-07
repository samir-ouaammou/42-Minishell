#include "../minishell.h"

void	ft_handle_redirect_content(t_parsing *shell, int *j, int *k)
{
	int	i;

	while (shell->tokens)
	{
		if (ft_check_is_operators(shell->tokens->value[0]))
			break ;
		i = 0;
		while (shell->tokens->value[i])
		{
			if (!(*k))
			{
				if (shell->tmp)
					shell->tmp = NULL;
				shell->tmp = ft_malloc((shell->tab[(*j)++] + 1)
						* sizeof(char *));
			}
			shell->tmp[*k] = ft_strdup(shell->tokens->value[i]);
			(*k)++;
			i++;
		}
		if (shell->tokens)
			shell->tokens = shell->tokens->next;
	}
	if (*k)
		shell->tmp[*k] = NULL;
}
