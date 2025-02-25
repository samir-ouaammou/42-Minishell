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
	int(i), (j);
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

char *process_template_string(char *str, t_data *data)
{
	char **split_str;
	int(i), (count);
	if (!str || !data)
		return (NULL);
	i = 0;
	split_str = ft_split(str, ' ');
	if (!split_str)
		return (NULL);
	count = 0;
	while (split_str[count])
		count++;
	char **res = malloc(sizeof(char *) * (count + 1));
	if (!res)
		return (NULL);
	while (i < count)
	{
		res[i] = malloc(calculate_length(split_str[i], data) + 1);
		if (!res[i])
			return (NULL);
		process_variable(split_str[i], res[i], data);
		i++;
	}
	// ft_printf("split_str: %s\n", res[0]);
	res[count] = NULL;
	i = 0;
	int len = 0;
	while (res[i])
	{
		len += ft_strlen(res[i]);
		i++;
	}
	char *res_str = malloc(len + 1);
	if (!res_str)
		return (NULL);
	i = 0;
	int j = 0;
	int k = 0;
	while (res[i])
	{
		j = 0;
		while (res[i][j])
		{
			res_str[k++] = res[i][j];
			j++;
		}
		if (res[i + 1])
			res_str[k++] = ' ';
		i++;
	}
	res_str[len] = '\0';
	return (res_str);
}
