/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahaded <aahaded@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:13:36 by aahaded           #+#    #+#             */
/*   Updated: 2025/02/16 18:13:38 by aahaded          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	remove_env_var(t_data *data, int index)
{
	while (data->env[index + 1])
	{
		data->env[index] = data->env[index + 1];
		index++;
	}
	data->env[index] = NULL;
}

int	builtin_unset(t_ast *node, t_data *data)
{
	int	i;
	int	j;

	if (!node || !data || !data->env)
		return (1);
	i = 1;
	while (node->value[i])
	{
		j = 0;
		while (data->env[j])
		{
			if (ft_strncmp(node->value[i], data->env[j],
					ft_strlen(node->value[i])) == 0)
			{
				remove_env_var(data, j);
				break ;
			}
			j++;
		}
		i++;
	}
	return (0);
}
