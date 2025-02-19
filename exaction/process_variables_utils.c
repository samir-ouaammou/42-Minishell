/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_variables_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahaded <aahaded@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:27:50 by aahaded           #+#    #+#             */
/*   Updated: 2025/02/17 16:27:52 by aahaded          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	copy_string(char *str, char *res)
{
	int(i), (j);
	i = 1;
	j = 0;
	while (str[i])
	{
		if (str[i] != '$')
			res[j++] = str[i];
		else
			break ;
		i++;
	}
	res[j] = '\0';
}

static int	calculate_length(char *str)
{
	int(len), (i);
	len = 0;
	i = 1;
	while (str[i])
	{
		if (str[i] != '$')
			len++;
		i++;
	}
	return (len);
}

char	*get_str_Dollars(char *str)
{
	int		len;
	char	*res;

	len = calculate_length(str);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	copy_string(str, res);
	return (res);
}

size_t	handle_env_var_length(char *str, t_data *data, int *index)
{
	size_t	len;
	char	*var;
	char	*env_var;
	char	*chrstr;

	len = 0;
	var = get_str_Dollars(&str[*index]);
	if (var)
	{
		len += ft_strlen(var);
		env_var = find_str_env(ft_strjoin(var, "="), data);
		if (env_var)
		{
			chrstr = ft_strchr(env_var, '=');
			if (chrstr)
				len += ft_strlen(chrstr) - 1;
		}
		*index += ft_strlen(var) + 1;
	}
	return (len);
}

size_t	handle_exit_status_length(t_data *data, int *index)
{
	size_t	len;
	char	*exit_status;

	len = 0;
	exit_status = ft_itoa(data->exit_status);
	if (exit_status)
		len += ft_strlen(exit_status);
	*index += 2;
	return (len);
}
