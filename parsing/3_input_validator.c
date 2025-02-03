#include "../libft/libft.h"
#include "Minishell.h"

void	ft_check_the_brackets(t_parsing *shell)
{
	if (shell->free == -1)
		return ;
	shell->i = 0;
	while (shell->temp[shell->i])
	{
		shell->j = 0;
		while (shell->temp[shell->i][shell->j] && shell->temp[shell->i][0] != 34
			&& shell->temp[shell->i][0] != 39
			&& shell->temp[shell->i][ft_strlen(shell->temp[shell->i]) - 1] != 34
			&& shell->temp[shell->i][ft_strlen(shell->temp
				[shell->i]) - 1] != 39)
		{
			if (shell->temp[shell->i][shell->j] == '(')
				shell->brackets++;
			if (shell->temp[shell->i][shell->j] == ')')
				shell->brackets--;
			shell->j++;
		}
		if (shell->brackets < 0)
		{
			ft_free_args(shell);
			return ;
		}
		shell->i++;
	}
}

t_list	*ft_creat_new_node(t_parsing *shell, int start, int end)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->value = malloc((end - start + 2) * sizeof(char *));
	if (!new->value)
		return (NULL);
	shell->len = 0;
	while (start <= end)
	{
		new->value[shell->len] = ft_strdup(shell->temp[start]);
		shell->len++;
		start++;
	}
	new->value[shell->len] = NULL;
	new->next = NULL;
	return (new);
}

int	ft_is_symbol(t_parsing *shell)
{
	if (!shell->temp[shell->i])
		return (0);
	if (!ft_strcmp(shell->temp[shell->i], "|")
		|| !ft_strcmp(shell->temp[shell->i], ")")
		|| !ft_strcmp(shell->temp[shell->i], "(")
		|| !ft_strcmp(shell->temp[shell->i], "<")
		|| !ft_strcmp(shell->temp[shell->i], ">")
		|| !ft_strcmp(shell->temp[shell->i], "<<")
		|| !ft_strcmp(shell->temp[shell->i], ">>")
		|| !ft_strcmp(shell->temp[shell->i], "||")
		|| !ft_strcmp(shell->temp[shell->i], "&&"))
		return (1);
	return (0);
}

void	ft_tokens_list(t_parsing *shell)
{
	if (!shell || !shell->temp || !shell->temp[0])
		return ;
	shell->i = 0;
	while (shell->temp[shell->i])
	{
		shell->j = shell->i;
		if (!ft_is_symbol(shell) && !ft_is_redirections(shell, shell->i))
		{
			while (shell->temp[shell->i] && !ft_is_symbol(shell)
				&& !ft_is_redirections(shell, shell->i))
				shell->i++;
		}
		else if (ft_is_symbol(shell))
			shell->i++;
		shell->lst_help1 = ft_creat_new_node(shell, shell->j, --shell->i);
		if (!shell->lst_help1)
			return ;
		if (!shell->tokens)
			shell->tokens = shell->lst_help1;
		else
			shell->lst_help2->next = shell->lst_help1;
		shell->lst_help2 = shell->lst_help1;
		shell->i++;
	}
}

void	ft_check_syntax_errors(t_parsing *shell)
{
	ft_check_the_brackets(shell);
	if (shell->brackets != 0)
		ft_free_args(shell);
	ft_check_operator_position(shell);
	ft_tokens_list(shell);
}
