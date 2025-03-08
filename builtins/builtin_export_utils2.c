/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahaded <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 23:30:57 by aahaded           #+#    #+#             */
/*   Updated: 2025/03/06 23:30:58 by aahaded          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	add_default_export(char *str, t_exaction *data, int len)
{
	char	**new_export;
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (data->export[i])
	{
		if (ft_strncmp(data->export[i], str, len) == 0)
			return (1);
		i++;
	}
	i = -1;
	count = count_export_entries(data);
	new_export = ft_malloc(sizeof(char *) * (count + 2));
	if (!new_export)
		return (1);
	while (++i < count)
		new_export[i] = ft_strdup(data->export[i]);
	new_export[i] = ft_strdup(str);
	new_export[i + 1] = NULL;
	data->export = new_export;
	return (0);
}

int	add_new_env_var(char **args, t_exaction *data, int index)
{
	char	**new_env;
	int		count;
	int		i;

	count = 0;
	i = 0;
	if (data->env)
	{
		while (data->env[count])
			count++;
	}
	new_env = ft_malloc(sizeof(char *) * (count + 2));
	if (!new_env)
		return (1);
	while (i < count)
	{
		new_env[i] = ft_strdup(data->env[i]);
		i++;
	}
	new_env[i] = ft_strdup(args[index]);
	new_env[i + 1] = NULL;
	data->env = new_env;
	return (0);
}

int	add_new_export_var(char **args, t_exaction *data, int index)
{
	char	**new_export;
	int		count;
	int		i;

	count = 0;
	i = -1;
	if (data->export)
	{
		while (data->export[count])
			count++;
	}
	new_export = ft_malloc(sizeof(char *) * (count + 2));
	if (!new_export)
		return (1);
	while (++i < count)
		new_export[i] = ft_strdup(data->export[i]);
	new_export[i] = ft_strdup(args[index]);
	new_export[i + 1] = NULL;
	data->export = new_export;
	return (0);
}

int	is_valid_export_identifier(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[0] == '-' || str[0] == '+' || str[0] == '='
			|| ft_isdigit(str[0]) || !ft_isalpha(str[0]))
			return (1);
		else if ((!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '+'))
			return (1);
		i++;
	}
	return (0);
}

int	check_plus(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		if (str[i] == '+' && (str[i + 1] != '='))
			return (1);
		i++;
	}
	return (0);
}
