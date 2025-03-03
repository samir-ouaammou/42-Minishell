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
	(void)data;
	(void)str;
	size_t len;
	int i;

	len = 0;
	i = 0;
	while (str[i])
	{
		if ((str[i] == '$' && str[i + 1] != '?' && str[i + 1] != '\0') && str[i + 1] != '$' && str[i + 1] != '*')
			len += handle_env_var_length(str, data, &i);
		else if (str[i] == '$' && str[i + 1] == '?' && str[i + 1] != '$')
			len += handle_exit_status_length(data, &i);
		else
		{
			len++;
			i++;
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
		char *str_j = ft_strjoin(var, "=");
		if (!str_j)
			return;

		env_var = find_str_env(str_j, data);
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

void process_variable(char *str, char *res, t_data *data)
{
	int i, res_index;

	i = 0;
	res_index = 0;
	
	while (str[i])
	{

		if ((str[i] == '$' && str[i + 1] != '?' && str[i + 1] != '\0') && str[i + 1] != '$' && str[i + 1] != '*')
		{
			handle_env_var(&str[i], res, data, &res_index);
			i += ft_strlen(get_str_Dollars(&str[i])) + 1;
		}
		else if (str[i] == '$' && str[i + 1] == '?' && str[i + 1] != '$')
		{
			handle_exit_status(res, data, &res_index);
			i += 2;
		}
		else
		{
			res[res_index] = str[i];
			res_index++;
			i++;
		}
	}
	res[res_index] = '\0';
}

char  *process_strings(char *str, t_data *data)
{
	char	*res_str;
	int		len = 0;

	len = calculate_length(str, data);
	res_str = malloc(len + 1);
	if (!res_str)
		return (NULL);
	process_variable(str, res_str, data);
	return (res_str);
}