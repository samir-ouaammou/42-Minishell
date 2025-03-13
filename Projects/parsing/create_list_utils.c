/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaammo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 01:02:17 by souaammo          #+#    #+#             */
/*   Updated: 2025/03/08 01:02:18 by souaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

int	ft_count_nodes_list(t_list *list)
{
	int	count;

	count = 0;
	while (list)
	{
		count++;
		list = list->next;
	}
	return (count);
}

t_list	*ft_creat_new_node(t_parsing *shell, int start, int end)
{
	t_list	*new;

	new = ft_malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->value = ft_malloc((end - start + 2) * sizeof(char *));
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

void	ft_initialize_tab(t_parsing *shell)
{
	shell->j = 0;
	shell->i = -1;
	while (++shell->i < 999)
		shell->tab[shell->i] = 0;
	shell->lst_help1 = shell->tokens;
}

void	ft_process_redirections(t_parsing *shell)
{
	shell->lst_help1 = shell->lst_help1->next;
	shell->j++;
	while (shell->lst_help1)
	{
		if (ft_check_is_operators(shell->lst_help1->value[0]))
			break ;
		shell->i = -1;
		while (shell->lst_help1->value[++shell->i])
			;
		shell->tab[shell->j] += shell->i;
		shell->lst_help1 = shell->lst_help1->next;
	}
	shell->j++;
}

void	ft_count_len_list(t_parsing *shell)
{
	ft_initialize_tab(shell);
	while (shell->lst_help1)
	{
		shell->i = -1;
		while (shell->lst_help1->value[++shell->i])
			;
		shell->tab[shell->j] = shell->i;
		if (ft_check_is_redirections(shell->lst_help1->value[0]))
			ft_process_redirections(shell);
		else
		{
			shell->lst_help1 = shell->lst_help1->next;
			shell->j++;
		}
	}
	shell->len = shell->j;
}
