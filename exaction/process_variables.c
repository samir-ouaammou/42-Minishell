/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahaded <aahaded@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:28:01 by aahaded           #+#    #+#             */
/*   Updated: 2025/02/17 16:28:03 by aahaded          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t calculate_length(char *str, t_data *data)
{
	size_t len;
	int index;

	len = 0;
	index = 0;
	while (str[index])
	{
		if (str[index] == '$' && str[index + 1] != '?')
			len += handle_env_var_length(str, data, &index);
		else if (str[index] == '$' && str[index + 1] == '?')
			len += handle_exit_status_length(data, &index);
		else
		{
			len++;
			index++;
		}
	}
	return (len);
}

void handle_env_var(char *str, char *res, t_data *data, int *res_index)
{
	char(*var), (*chrstr), (*env_var);
	var = get_str_Dollars(str);
	if (var)
	{
		env_var = find_str_env(ft_strjoin(var, "="), data);
		if (env_var)
		{
			chrstr = ft_strchr(env_var, '=');
			if (chrstr)
			{
				ft_strcpy(&res[*res_index], chrstr + 1);
				*res_index += ft_strlen(chrstr) - 1;
			}
		}
	}
}

static void handle_exit_status(char *res, t_data *data, int *res_index)
{
	char *exit_status;

	exit_status = ft_itoa(data->exit_status);
	if (exit_status)
	{
		ft_strcpy(&res[*res_index], exit_status);
		*res_index += ft_strlen(exit_status);
	}
}

void process_variable(char *str, char *res, t_data *data, int *res_index)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != '?' && str[i + 1] != '\0' && str[0] != '\'' && str[i + 1] != '$')
		{
			handle_env_var(&str[i], res, data, res_index);
			i += ft_strlen(get_str_Dollars(&str[i])) + 1;
		}
		else if (str[i] == '$' && str[i + 1] == '?' && str[0] != '\'' && str[i + 1] != '$')
		{
			handle_exit_status(res, data, res_index);
			i += 2;
		}
		else
		{
			res[*res_index] = str[i];
			(*res_index)++;
			i++;
		}
	}
	res[*res_index] = '\0';
}

void process_strings(t_ast *root, t_data *data)
{
	char **res;

	int(i), (count), (res_index);
	if (!root || !root->value || !data)
		return;
	count = 0;
	while (root->value[count])
		count++;
	res = malloc(sizeof(char *) * (count + 1));
	if (!res)
		return;
	i = 0;
	while (i < count)
	{
		res[i] = malloc(calculate_length(root->value[i], data) + 1);
		if (!res[i])
			return;
		res_index = 0;
		process_variable(root->value[i], res[i], data, &res_index);
		i++;
	}
	res[count] = NULL;
	root->value = res;
}
