/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils3.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahaded <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 23:33:30 by aahaded           #+#    #+#             */
/*   Updated: 2025/03/06 23:33:31 by aahaded          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

int	update_env_var(char **args, t_exaction *data, char *str, int i)
{
	int		j;
	char	*str_j;

	j = -1;
	if (!data->env)
		return (0);
	while (data->env[++j])
	{
		if (ft_strncmp(data->env[j], args[i], (ft_strlen(args[i])
					- ft_strlen(str))) == 0)
		{
			if (data->is_plus == 1)
			{
				str_j = ft_strjoin(data->env[j], str + 1);
				if (!str_j)
					return (0);
				data->env[j] = str_j;
			}
			else
				data->env[j] = ft_strdup(args[i]);
			return (1);
			break ;
		}
	}
	return (0);
}

char	*get_key_part(char *str, char delimiter)
{
	char	*result;
	char	*pos;
	int		len;

	pos = ft_strchr(str, delimiter);
	if (pos)
	{
		len = (ft_strlen(str) - ft_strlen(pos)) + 1;
		result = ft_malloc(len + 1);
		if (!result)
			return (NULL);
		ft_strncpy(result, str, len);
		result[len] = '\0';
		return (result);
	}
	return (NULL);
}

void	add_quoted_export_entry(t_exaction *data, char *str, int j)
{
	char	*str_new;

	str_new = add_double_quotes(str);
	data->export[j] = ft_strdup(str_new);
}

int	update_export_var(char **args, t_exaction *data, char *str, int i)
{
	int	j;

	j = -1;
	if (!data->export)
		return (0);
	while (data->export[++j])
	{
		if (ft_strncmp(data->export[j], args[i], (ft_strlen(args[i])
					- ft_strlen(str))) == 0)
		{
			if (data->is_plus == 1)
				update_export_with_quotes(data, args[i], j, str);
			else
				add_quoted_export_entry(data, args[i], j);
			return (1);
		}
	}
	return (0);
}

int	count_export_entries(t_exaction *data)
{
	int	count;

	count = 0;
	if (data->export)
	{
		while (data->export[count])
			count++;
	}
	return (count);
}
