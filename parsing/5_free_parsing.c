#include "../libft/libft.h"
#include "Minishell.h"

void	ft_free_parsing(t_parsing *shell)
{
	if (shell->input)
	{
		free(shell->input);
		shell->input = NULL;
	}
	if (shell->free != -1)
		ft_free_args(shell);
	if (shell->tokens)
		ft_free_tokens(shell);
	if (shell->three)
		ft_free_ast(shell->three);
}

void	ft_free_ast(t_ast *node)
{
	int	i;

	if (!node)
		return ;
	if (node->value)
	{
		i = 0;
		while (node->value[i])
		{
			free(node->value[i]);
			node->value[i] = NULL;
			i++;
		}
		free(node->value);
		node->value = NULL;
	}
	ft_free_ast(node->left);
	ft_free_ast(node->right);
	free(node);
	node = NULL;
}

void	ft_free_tokens(t_parsing *shell)
{
	if (!shell || !shell->tokens)
		return ;
	while (shell->tokens)
	{
		shell->i = 0;
		if (shell->tokens->value)
		{
			while (shell->tokens->value[shell->i])
			{
				free(shell->tokens->value[shell->i]);
				shell->tokens->value[shell->i] = NULL;
				shell->i++;
			}
			free(shell->tokens->value);
			shell->tokens->value = NULL;
		}
		shell->lst_help1 = shell->tokens;
		shell->tokens = shell->tokens->next;
		free(shell->lst_help1);
	}
}

void	ft_free_args(t_parsing *shell)
{
	if (!shell || shell->free == -1)
		return ;
	shell->free = -1;
	if (shell->cmds != NULL)
		free(shell->cmds);
	if (shell->temp)
	{
		shell->i = 0;
		while (shell->temp[shell->i])
		{
			if (shell->temp[shell->i] != NULL)
			{
				free(shell->temp[shell->i]);
				shell->temp[shell->i] = NULL;
			}
			shell->i++;
		}
		free(shell->temp);
		shell->temp = NULL;
	}
}
