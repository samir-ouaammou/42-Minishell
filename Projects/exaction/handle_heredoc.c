/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaammo <souaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:50:08 by aahaded           #+#    #+#             */
/*   Updated: 2025/03/03 13:53:40 by souaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

int	open_input_file(t_ast *node, t_exaction *data)
{
	int	fd_file;

	node->right->value[0] = process_strings(node->right->value[0], data);
	fd_file = open(node->right->value[0], O_RDONLY);
	if (fd_file == -1)
	{
		ft_printf("minishella: %s: %s\n", node->right->value[0],
			strerror(errno));
	}
	return (fd_file);
}

int	execute_heredoc(t_ast *node, t_exaction *data)
{
	int	i;
	int	fd_out;
	int	fd_in;

	i = 0;
	fd_in = open_input_file(node, data);
	if (fd_in == -1)
	{
		data_struc()->exit_status = 1;
		return (1);
	}
	while (node->right->value[i])
	{
		if (handle_redirection(node, &i, &fd_out, &fd_in))
		{
			data_struc()->exit_status = 1;
			return (1);
		}
		i++;
	}
	return (setup_redirections(node, data, fd_out, fd_in));
}
