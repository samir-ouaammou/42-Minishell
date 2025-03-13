/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahaded <aahaded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:13:36 by aahaded           #+#    #+#             */
/*   Updated: 2025/03/03 12:19:54 by aahaded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

static void	remove_env_var(t_exaction *data, int index)
{
	while (data->env[index + 1])
	{
		data->env[index] = data->env[index + 1];
		index++;
	}
	data->env[index] = NULL;
}

static void	remove_export_var(t_exaction *data, int index)
{
	while (data->export[index + 1])
	{
		data->export[index] = data->export[index + 1];
		index++;
	}
	data->export[index] = NULL;
}

static int	remove_var_from_env(char *arg, t_exaction *data)
{
	int	j;

	j = 0;
	while (data->env[j])
	{
		if (ft_strncmp(arg, data->env[j], ft_strlen(arg)) == 0)
		{
			remove_env_var(data, j);
			return (1);
		}
		j++;
	}
	return (0);
}

static int	remove_var_from_export(char *arg, t_exaction *data)
{
	int	j;

	j = 0;
	while (data->export[j])
	{
		if (ft_strncmp(arg, data->export[j], ft_strlen(arg)) == 0)
		{
			remove_export_var(data, j);
			return (1);
		}
		j++;
	}
	return (0);
}

int	builtin_unset(char **args, t_exaction *data)
{
	int	i;

	i = 0;
	if (!args || !data || !data->env || !data->export)
	{
		data_struc()->exit_status = 1;
		return (1);
	}
	i = 1;
	while (args[i])
	{
		if (is_assignment_format(args[i]))
		{
			i++;
			continue ;
		}
		remove_var_from_env(args[i], data);
		remove_var_from_export(args[i], data);
		i++;
	}
	data_struc()->exit_status = 0;
	return (0);
}
