/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahaded <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 23:18:05 by aahaded           #+#    #+#             */
/*   Updated: 2025/03/06 23:18:06 by aahaded          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	remove_quotes_from_string(char *str_export, char *res)
{
	int	j;
	int	index;

	j = 0;
	index = 0;
	while (str_export[index])
	{
		if (str_export[index] != '"')
		{
			res[j] = str_export[index];
			j++;
		}
		index++;
	}
	return (j);
}

char	*add_double_quotes_plus(char *str_export, char *str)
{
	char	*res;
	int		i;
	int		j;

	if (!str_export || !str)
		return (NULL);
	res = ft_malloc(strlen_without_quotes(str_export) + ft_strlen(str) + 1);
	if (!res)
		return (NULL);
	j = remove_quotes_from_string(str_export, res);
	i = 0;
	while (str[i])
	{
		res[j + i] = str[i];
		i++;
	}
	res[j + i] = '\0';
	return (res);
}

char	*test(char *str, char *res)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		res[j++] = str[i];
		if (str[i] == '=')
		{
			res[j++] = '"';
			i++;
			while (str[i])
				res[j++] = str[i++];
			res[j++] = '"';
			break ;
		}
		else
			i++;
	}
	res[j] = '\0';
	return (res);
}

char	*add_double_quotes(char *str)
{
	int		len;
	char	*res;

	if (!str)
		return (NULL);
	len = 0;
	while (str[len])
		len++;
	res = ft_malloc(len + 3);
	if (!res)
		return (NULL);
	return (test(str, res));
}

void	handle_plus_operator(int index, char **args)
{
	char	*res;
	int		j;
	int		k;

	j = 0;
	res = ft_malloc(strlen_without_plus(args[index]) + 1);
	if (!res)
		return ;
	j = 0;
	k = 0;
	while (args[index][j])
	{
		if (args[index][j] != '+')
			res[k++] = args[index][j];
		j++;
	}
	res[k] = '\0';
	args[index] = ft_strdup(res);
}
