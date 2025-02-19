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

static int update_env_var(char **args, t_data *data, char *str, int index)
{
	int j;
	int found;

	j = 0;
	found = 0;
	while (data->env[j])
	{
		if (ft_strncmp(data->env[j], args[index], (ft_strlen(args[index]) - ft_strlen(str))) == 0)
		{
			if (data->is_plus == 1)
			{
				char *str_j = ft_strjoin(data->env[j], str + 1);
				data->env[j] = ft_strdup(str_j);
			}
			else
				data->env[j] = ft_strdup(args[index]);
			found = 1;
			break;
		}
		j++;
	}
	return (found);
}

static int add_new_env_var(char **args, t_data *data, int index)
{
	char **new_env;
	int count = 0;
	int k = 0;

	while (data->env[count])
		count++;
	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
		return (1);
	while (k < count)
	{
		new_env[k] = strdup(data->env[k]);
		k++;
	}
	int i = 0;
	int j = 0;
	int len = 0;
	while (args[index][i])
	{
		if (args[index][i] != '+')
			len++;
		i++;
	}
	new_env[k] = malloc(len + 1);
	if (!new_env[k])
		return (1);
	i = 0;
	while (args[index][i])
	{
		if (args[index][i] != '+')
		{
			new_env[k][j] = args[index][i];
			j++;
		}
		i++;
	}
	new_env[k][j] = '\0';
	new_env[k + 1] = NULL;
	data->env = new_env;
	return (0);
}

int builtin_export(char **args, t_data *data)
{
	int i;
	int found;
	char *str;

	if (!args || !data || !data->env)
		return (1);
	i = 1;
	found = 0;
	data->is_plus = 0;
	str = NULL;
	while (args[i])
	{
		int j = 0;
		int check_error = 0;
		while (args[i][j])
		{
			if (args[i][0] == '=' || args[i][0] == '+' || (args[i][j] == '+' && args[i][j + 1] != '=') || ((args[i][0] == '-') || (args[i][j] == '-')))
			{
				ft_printf("minishell: export: `%s': not a valid identifier\n", args[i]);
				check_error = 1;
				break;
			}
			j++;
		}
		str = ft_strchr(args[i], '=');
		if (!str || check_error || (args[i][0] == '_' && args[i][1] == '='))
		{
			i++;
			continue;
		}
		j = 0;
		while (args[i][j])
		{
			if (args[i][j] == '+')
				data->is_plus = 1;
			if (args[i][j] == '=')
				break;
			j++;
		}
		if (data->is_plus == 1)
		{
			int len = 0;
			int j = 0;
			while (args[i][j])
			{
				if (args[i][j] != '+')
					len++;
				j++;
			}
			char *res = malloc(len);
			if (!res)
				return (1);
			j = 0;
			int k = 0;
			while (args[i][j])
			{
				if (args[i][j] != '+')
				{
					res[k] = args[i][j];
					k++;
				}
				j++;
			}
			res[k] = '\0';
			args[i] = ft_strdup(res);
		}
		found = update_env_var(args, data, str, i);
		if (!found)
			add_new_env_var(args, data, i);
		i++;
	}
	return (0);
}
