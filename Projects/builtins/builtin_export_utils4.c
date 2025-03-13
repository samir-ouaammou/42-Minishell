/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils4.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahaded <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 23:42:43 by aahaded           #+#    #+#             */
/*   Updated: 2025/03/06 23:42:44 by aahaded          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_export(t_exaction *data)
{
	int	i;

	i = 0;
	if (!data || !data->export)
		return ;
	while (data->export[i])
	{
		if (data->export[i])
			printf("declare -x %s\n", data->export[i]);
		i++;
	}
}

int	strlen_without_plus(char *arg)
{
	int	j;
	int	len;

	j = 0;
	len = 0;
	while (arg[j])
	{
		if (arg[j] != '+')
			len++;
		j++;
	}
	return (len);
}

void	update_export_with_quotes(t_exaction *data, char *arg, int j, char *str)
{
	char	*get_key;
	char	*str_j;

	get_key = NULL;
	str_j = NULL;
	if (!is_assignment_format(data->export[j]))
	{
		str_j = ft_strjoin(data->export[j], "=");
		str_j = ft_strjoin(str_j, add_double_quotes(str) + 1);
		data->export[j] = str_j;
	}
	else
	{
		get_key = get_key_part(arg, '=');
		str_j = ft_strjoin(get_key,
				add_double_quotes_plus((ft_strchr(data->export[j], '=') + 1),
					str + 1));
		data->export[j] = add_double_quotes(str_j);
	}
}

int	strlen_without_quotes(char *str_export)
{
	int	len;
	int	index;

	len = 0;
	index = 0;
	while (str_export[index])
	{
		if (str_export[index] != '"')
			len++;
		index++;
	}
	return (len);
}
