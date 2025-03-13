/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaammo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 01:04:11 by souaammo          #+#    #+#             */
/*   Updated: 2025/03/08 01:04:12 by souaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

void	handle_operators(t_list **tmp, char **str)
{
	int	i;

	i = 0;
	while (*tmp && (*tmp)->value && ft_check_is_operators((*tmp)->value[0]))
	{
		i = 0;
		while ((*tmp) && (*tmp)->value[i])
		{
			*str = ft_strjoin_and_free(*str, (*tmp)->value[i]);
			*str = ft_strjoin_and_free(*str, " ");
			i++;
		}
		*tmp = (*tmp)->next;
	}
}

void	ft_init_move_vars(t_parsing *shell, int *i, int *j, int *k)
{
	*i = 0;
	*j = 0;
	*k = 0;
	shell->tmp = NULL;
	ft_count_len_list(shell);
	shell->lst_help1 = shell->tokens;
}

void	handle_non_operator(t_list **tmp, char **str)
{
	int	i;

	i = 0;
	while (*tmp && (*tmp)->value && !ft_check_is_operators((*tmp)->value[0])
		&& !ft_check_is_redirections((*tmp)->value[0]))
	{
		i = 0;
		while (*tmp && (*tmp)->value[i])
		{
			*str = ft_strjoin_and_free(*str, (*tmp)->value[i]);
			*str = ft_strjoin_and_free(*str, " ");
			i++;
		}
		*tmp = (*tmp)->next;
	}
}

void	handle_redirections(t_parsing *shell, t_list **tmp, char **str)
{
	t_list	*help;
	char	*redirections;

	help = *tmp;
	redirections = ft_move_flags(shell, help);
	if (!redirections)
		return ;
	*str = ft_strjoin_and_free(*str, redirections);
	*str = ft_strjoin_and_free(*str, " ");
	while (*tmp && (*tmp)->value && !ft_check_is_operators((*tmp)->value[0]))
		*tmp = (*tmp)->next;
}

void	ft_pars_redirections(t_parsing *shell, t_list *list)
{
	t_list	*tmp;
	char	*str;

	tmp = list;
	str = ft_malloc(ft_strlen(shell->input));
	if (!str)
	{
		write(2, "Error: Memory allocation failed.\n", 33);
		ft_exit(-1);
	}
	str[0] = '\0';
	while (tmp)
	{
		handle_operators(&tmp, &str);
		handle_non_operator(&tmp, &str);
		if (tmp && tmp->value && ft_check_is_redirections(tmp->value[0]))
		{
			handle_redirections(shell, &tmp, &str);
		}
		if (tmp && tmp->value && !ft_check_is_operators(tmp->value[0]))
			tmp = tmp->next;
	}
	ft_free_parsing(shell);
	ft_init_parsing(shell);
	shell->input = str;
}
