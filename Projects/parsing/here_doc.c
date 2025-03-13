/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaammo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 01:02:28 by souaammo          #+#    #+#             */
/*   Updated: 2025/03/08 01:02:30 by souaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

void	process_input(t_parsing *shell, char *str)
{
	while (str[shell->i])
	{
		if (str[shell->i] == '\t')
		{
			shell->itoa = ft_itoa(shell->nbr);
			shell->name = ft_strjoin("/tmp/heredoc", shell->itoa);
			while (str[shell->i] && str[shell->i] == '\t')
				shell->i++;
			shell->len = 0;
			while (shell->name[shell->len])
			{
				shell->help[shell->j++] = shell->name[shell->len];
				shell->len++;
			}
			shell->nbr++;
		}
		shell->help[shell->j++] = str[shell->i];
		if (str[shell->i])
			shell->i++;
	}
}

int	ft_process_delimiter(t_parsing *shell, char *str, t_exaction *data,
		int *dolar)
{
	int	h;

	shell->stop[0] = ft_substr(str, shell->i, shell->j - shell->i);
	h = 0;
	while (shell->stop && shell->stop[0] && shell->stop[0][h])
	{
		if (shell->stop[0][h] == 39)
		{
			*dolar = 1;
			break ;
		}
		h++;
	}
	ft_remove_quots(shell->stop, data, 0);
	shell->itoa = ft_itoa(shell->nbr);
	shell->name = ft_strjoin("/tmp/heredoc", shell->itoa);
	shell->fd = open(shell->name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	return (handle_forked_process(shell, *dolar, data));
}

int	ft_check_unclosed_quotes(t_parsing *shell, char *str)
{
	if (!str[shell->j] && shell->chr != ' ')
	{
		while (1)
		{
			shell->line = readline("heredoc> ");
		}
		return (1);
	}
	return (0);
}

void	ft_read_and_process_heredoc_input(t_parsing *shell, int dolar,
		t_exaction *data)
{
	while (1)
	{
		shell->line = readline("heredoc> ");
		if (!shell->line)
			return ;
		if (!ft_strcmp(shell->stop[0], shell->line))
			return ;
		if (!dolar)
			shell->line = process_strings(shell->line, data);
		write(shell->fd, shell->line, ft_strlen(shell->line));
		write(shell->fd, "\n", 1);
	}
}

void	ft_here_doc(t_parsing *shell, t_exaction *data, char *str, int dolar)
{
	int	nbr;

	if (!str || !str[0])
		return ;
	ft_init_here_doc(shell);
	while (str[shell->i])
	{
		if (str[shell->i] == 34 || str[shell->i] == 39)
			ft_handle_quotes(shell, str);
		else if (str[shell->i] == '<' && str[shell->i + 1] == '<')
		{
			if (!ft_check_delimiter(shell, str))
				return ;
			ft_find_delimiter_end(shell, str);
			if (ft_check_unclosed_quotes(shell, str))
				return ;
			nbr = ft_process_delimiter(shell, str, data, &dolar);
			if (nbr == 1)
				return ;
			ft_update_position(shell, str);
		}
		else
			shell->i++;
	}
	ft_finalize_here_doc(shell, str);
}
