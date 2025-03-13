/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaammo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 01:02:36 by souaammo          #+#    #+#             */
/*   Updated: 2025/03/08 01:02:37 by souaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

void	ft_handle_quotes(t_parsing *shell, char *str)
{
	shell->chr = str[shell->i++];
	while (str[shell->i] && str[shell->i] != shell->chr)
		shell->i++;
	if (str[shell->i])
		shell->i++;
}

int	ft_check_delimiter(t_parsing *shell, char *str)
{
	shell->i += 2;
	shell->chr = ' ';
	while (str[shell->i] && str[shell->i] == ' ')
		shell->i++;
	if (ft_is_single_operator(str[shell->i]) || !str[shell->i])
	{
		ft_free_args(shell);
		return (0);
	}
	if (shell->bol == 0)
		shell->start = shell->i;
	shell->bol = 1;
	return (1);
}

void	ft_find_delimiter_end(t_parsing *shell, char *str)
{
	shell->j = shell->i;
	while (str[shell->j] && str[shell->j] != ' '
		&& !ft_is_single_operator(str[shell->j]))
	{
		if (str[shell->j] == 34 || str[shell->j] == 39)
		{
			shell->chr = str[shell->j++];
			while (str[shell->j] && str[shell->j] != shell->chr)
				shell->j++;
			if (shell->chr == str[shell->j])
				shell->chr = ' ';
		}
		if (str[shell->j])
			shell->j++;
	}
}

void	ft_update_position(t_parsing *shell, char *str)
{
	shell->i = shell->j;
	shell->end = shell->j;
	while (str[shell->j] && str[shell->j] == ' ')
		shell->j++;
	if (str[shell->j] && (str[shell->j] == '>' || str[shell->j] == '|'
			|| str[shell->j] == '&' || !str[shell->j]))
	{
		while (shell->start < shell->end)
		{
			str[shell->start] = '\t';
			shell->start++;
		}
		shell->bol = 0;
		shell->nbr++;
	}
}

void	ft_finalize_here_doc(t_parsing *shell, char *str)
{
	while (shell->start < shell->end)
	{
		str[shell->start] = '\t';
		shell->start++;
	}
	ft_move_input(shell, str);
}
