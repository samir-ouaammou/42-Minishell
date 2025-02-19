/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redirection_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahaded <aahaded@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:27:26 by aahaded           #+#    #+#             */
/*   Updated: 2025/02/17 16:27:27 by aahaded          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_input_file(t_ast *node)
{
	int	fd_file;

	fd_file = open(node->right->value[0], O_RDONLY);
	if (fd_file == -1)
		perror("Error");
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
