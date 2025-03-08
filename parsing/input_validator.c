/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaammo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 01:03:36 by souaammo          #+#    #+#             */
/*   Updated: 2025/03/08 01:03:38 by souaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cleanup_tokens(t_parsing *shell, t_list *head)
{
	if (shell->tmp)
		shell->tmp = NULL;
	shell->tokens = NULL;
	shell->lst_help1 = NULL;
	shell->lst_help2 = NULL;
	shell->tokens = head;
}

void	ft_handle_redirections(t_parsing *shell, t_list **head, int *j, int *k)
{
	t_list	*new;

	if (shell->tmp[0])
	{
		new = ft_lstnew(shell->tmp);
		ft_lstadd_back(head, new);
		if (shell->tmp)
			shell->tmp = NULL;
	}
	shell->tokens = shell->tokens->next;
	*k = 0;
	ft_handle_redirect_content(shell, j, k);
}

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
			&& shell->temp[shell->i][ft_strlen(shell->temp[shell->i])
			- 1] != 39)
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

void	ft_check_syntax_errors(t_parsing *shell)
{
	ft_check_the_brackets(shell);
	if (shell->brackets != 0)
		ft_free_args(shell);
	ft_check_operator_position(shell);
	ft_tokens_list(shell);
}
