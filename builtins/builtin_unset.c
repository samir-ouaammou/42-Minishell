/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaammo <souaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:13:36 by aahaded           #+#    #+#             */
/*   Updated: 2025/03/02 16:13:20 by souaammo         ###   ########.fr       */
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

static void	remove_export_var(t_data *data, int index)
{
	while (data->export[index + 1])
	{
		data->export[index] = data->export[index + 1];
		index++;
	}
	data->export[index] = NULL;
}

int	builtin_unset(char **args, t_data *data)
{
	int	i;
	int	j;

	if (!args || !data || !data->env || !data->export)
	{
		data->exit_status = 1;
		return (1);
	}
	i = 1;
	while (args[i])
	{
		j = 0;
		while (data->env[j])
		{
			if (ft_strncmp(args[i], data->env[j],
					ft_strlen(args[i])) == 0)
			{
				remove_env_var(data, j);
				break ;
			}
			j++;
		}
		j = 0;
		while (data->export[j])
		{
			if (ft_strncmp(args[i], data->export[j],
					ft_strlen(args[i])) == 0)
			{
				remove_export_var(data, j);
				break ;
			}
			j++;
		}
		i++;
	}
	return (0);
}
