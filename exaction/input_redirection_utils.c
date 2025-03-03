/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redirection_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaammo <souaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:27:26 by aahaded           #+#    #+#             */
/*   Updated: 2025/03/03 12:19:54 by souaammo         ###   ########.fr       */
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
		ft_printf("minishell: %s: %s\n", node->right->value[0], strerror(errno));
		data->exit_status = 1;
	}
	return (fd_file);
}

char	**copy_args(char **args, int start, int count)
{
	int		i;
	char	**res;

	i = 0;
	res = malloc(sizeof(char *) * (count + 1));
	if (!res)
		return (NULL);
	while (i < count)
	{
		res[i] = ft_strdup(args[start + i]);
		i++;
	}
	res[count] = NULL;
	return (res);
}
