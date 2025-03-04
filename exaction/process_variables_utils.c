/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_variables_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaammo <souaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:27:50 by aahaded           #+#    #+#             */
/*   Updated: 2025/03/03 13:53:40 by souaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_valid_char(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_')
	   return (1);
	return (0);
}

void	copy_string(char *str, char *res)
{
	int(i), (j);
	i = 1;
	j = 0;
	while (str[i])
	{
		if (str[i] != '$' && is_valid_char(str[i]) == 1)
			res[j++] = str[i];
		else
			break ;
		i++;
	}
	res[j] = '\0';
}

static int	calculate_length_(char *str)
{
	int(len), (i);
	len = 0;
	i = 1;
	while (str[i])
	{
		if (str[i] != '$' && is_valid_char(str[i]) == 1)
			len++;
		i++;
	}
	return (len);
}

char	*get_str_Dollars(char *str)
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

size_t	handle_env_var_length(char *str, t_exaction *data, int *index)
{
	(void)data;
	(void)index;
	(void)str;
	size_t	len;
	char	*var;
	char	*env_var;
	char	*chrstr;

	len = 0;
	// ft_printf("str: %s\n", str);
	var = get_str_Dollars(&str[*index]);
	if (!var)
	   return (-1);
	if (var)
	{
		char *str_j = ft_strjoin(var, "=");
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

size_t	handle_exit_status_length(t_exaction *data, int *index)
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
