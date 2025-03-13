/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_handler_ast_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahaded <aahaded@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:26:38 by aahaded           #+#    #+#             */
/*   Updated: 2025/02/17 16:26:40 by aahaded          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_special_chars(char **args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!*args)
		return (1);
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (args[i][j] == '*')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	duplicate_value_array(t_ast *root, t_exaction *data)
{
	int	i;

	i = 0;
	while (root->value && root->value[i])
		i++;
	data->copy = ft_malloc((i + 1) * sizeof(char *));
	i = 0;
	while (root->value && root->value[i])
	{
		data->copy[i] = ft_strdup(root->value[i]);
		i++;
	}
	data->copy[i] = NULL;
}
