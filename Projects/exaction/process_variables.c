/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahaded <aahaded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:28:01 by aahaded           #+#    #+#             */
/*   Updated: 2025/03/03 13:53:40 by aahaded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

void	handle_env_var(char *str, char *res, t_exaction *data, int *res_index)
{
	char	*str_j;
	char	*var;
	char	*chrstr;
	char	*env_var;

	var = get_str_dollars(str);
	if (var)
	{
		str_j = ft_strjoin(var, "=");
		if (!str_j)
			return ;
		env_var = find_str_env(str_j, data);
		if (data->space)
			remove_extra_spaces(env_var);
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

static void	handle_exit_status(char *res, int *res_index)
{
	char	*exit_status;

	exit_status = ft_itoa(data_struc()->exit_status);
	if (exit_status)
	{
		ft_strcpy(&res[*res_index], exit_status);
		*res_index += ft_strlen(exit_status);
	}
}

int	process_exit_status(char *res, int *res_index)
{
	handle_exit_status(res, res_index);
	return (2);
}

void	process_variable(char *str, char *res, t_exaction *data)
{
	int	i;
	int	res_index;

	i = 0;
	res_index = 0;
	while (str[i])
	{
		if ((str[i] == '$' && str[i + 1] != '?' && str[i + 1] != '\0')
			&& str[i + 1] != '$' && str[i + 1] != '*')
		{
			handle_env_var(&str[i], res, data, &res_index);
			i += ft_strlen(get_str_dollars(&str[i])) + 1;
		}
		else if (str[i] == '$' && str[i + 1] == '?' && str[i + 1] != '$')
			i += process_exit_status(res, &res_index);
		else
			res[res_index++] = str[i++];
	}
	res[res_index] = '\0';
}

char	*process_strings(char *str, t_exaction *data)
{
	char	*res_str;
	int		len;

	len = calculate_length(str, data);
	res_str = ft_malloc(len + 1);
	if (!res_str)
		return (NULL);
	process_variable(str, res_str, data);
	return (res_str);
}
