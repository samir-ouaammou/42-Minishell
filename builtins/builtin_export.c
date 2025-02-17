/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahaded <aahaded@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:11:56 by aahaded           #+#    #+#             */
/*   Updated: 2025/02/16 18:11:58 by aahaded          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	update_env_var(t_ast *node, t_data *data, char *str, int index)
{
	int	j;
	int	found;

	j = 0;
	found = 0;
	while (data->env[j])
	{
		if (ft_strncmp(data->env[j], node->value[index], (str
					- node->value[index])) == 0)
		{
			data->env[j] = ft_strdup(node->value[index]);
			found = 1;
			break ;
		}
		j++;
	}
	return (found);
}

static int	add_new_env_var(t_ast *node, t_data *data, int index)
{
	char	**new_env;
	int		count;
	int		k;

	new_env = NULL;
	count = 0;
	k = 0;
	while (data->env[count])
		count++;
	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
		return (1);
	while (data->env[k])
	{
		new_env[k] = data->env[k];
		k++;
	}
	new_env[k] = ft_strdup(node->value[index]);
	new_env[k + 1] = NULL;
	data->env = new_env;
	return (0);
}

int	builtin_export(t_ast *node, t_data *data)
{
	int		i;
	int		found;
	char	*str;

	if (!node || !data || !data->env)
		return (1);
	i = 0;
	found = 0;
	str = NULL;
	while (node->value[i])
	{
		str = ft_strchr(node->value[i], '=');
		if (!str)
		{
			i++;
			continue ;
		}
		found = update_env_var(node, data, str, i);
		if (!found)
			add_new_env_var(node, data, i);
		i++;
	}
	return (0);
}
