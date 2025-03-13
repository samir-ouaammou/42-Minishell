/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaammo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 01:02:10 by souaammo          #+#    #+#             */
/*   Updated: 2025/03/08 01:02:12 by souaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

t_list	*ft_get_list_node(t_list *tokens, int index)
{
	int	i;

	i = 0;
	while (tokens && i < index)
	{
		tokens = tokens->next;
		i++;
	}
	return (tokens);
}

int	ft_count_brackets(t_list *list)
{
	int	count;

	count = 0;
	while (list)
	{
		if (list->value && (!ft_strcmp(list->value[0], "(")
				|| !ft_strcmp(list->value[0], ")")))
			count++;
		list = list->next;
	}
	return (count);
}

void	ft_check_other_errors(t_parsing *shell)
{
	t_list	*tmp;

	if (!shell || !shell->tokens)
	{
		ft_free_parsing(shell);
		return ;
	}
	tmp = shell->tokens;
	while (tmp)
	{
		if (tmp && tmp->next && tmp->next->value && tmp->value && !tmp->value[1]
			&& ft_check_is_redirections(tmp->value[0])
			&& ft_check_is_operators(tmp->next->value[0]))
		{
			ft_free_parsing(shell);
			return ;
		}
		tmp = tmp->next;
	}
}

int	ft_count_heredoc(t_parsing *shell)
{
	if (!shell || !shell->tokens)
	{
		ft_free_parsing(shell);
		return (0);
	}
	shell->len = 0;
	shell->lst_help1 = shell->tokens;
	while (shell->lst_help1)
	{
		if (shell->lst_help1->value && shell->lst_help1->value[0]
			&& !shell->lst_help1->value[1]
			&& !ft_strcmp(shell->lst_help1->value[0], "<<"))
			shell->len++;
		shell->lst_help1 = shell->lst_help1->next;
	}
	if (shell->len >= 17)
	{
		ft_free_parsing(shell);
		ft_free_args(shell);
		return (0);
	}
	return (1);
}
