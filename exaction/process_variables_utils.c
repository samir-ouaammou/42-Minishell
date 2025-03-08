/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_variables_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahaded <aahaded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:27:50 by aahaded           #+#    #+#             */
/*   Updated: 2025/03/03 13:53:40 by aahaded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	calculate_length(char *str, t_exaction *data)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (str[i])
	{
		if ((str[i] == '$' && str[i + 1] != '?' && str[i + 1] != '\0')
			&& str[i + 1] != '$' && str[i + 1] != '*')
			len += handle_env_var_length(str, data, &i);
		else if (str[i] == '$' && str[i + 1] == '?' && str[i + 1] != '$')
			len += handle_exit_status_length(&i);
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

char	*get_str_dollars(char *str)
{
	int		len;
	char	*res;

	len = calculate_length_(str);
	res = ft_malloc(len + 1);
	if (!res)
		return (NULL);
	copy_string(str, res);
	return (res);
}

int	handle_env_var_length(char *str, t_exaction *data, int *index)
{
	int		len;
	char	*var;
	char	*env_var;
	char	*chrstr;
	char	*str_j;

	len = 0;
	var = get_str_dollars(&str[*index]);
	if (!var)
		return (-1);
	if (var)
	{
		str_j = ft_strjoin(var, "=");
		if (!str_j)
			return (1);
		env_var = find_str_env(str_j, data);
		if (env_var)
		{
			chrstr = ft_strchr(env_var, '=');
			if (chrstr)
				len += ft_strlen(chrstr + 1);
		}
		*index += ft_strlen(var) + 1;
	}
	return (len);
}

int	handle_exit_status_length(int *index)
{
	int		len;
	char	*exit_status;

	len = 0;
	exit_status = ft_itoa(data_struc()->exit_status);
	if (exit_status)
		len += ft_strlen(exit_status);
	*index += 2;
	return (len);
}
