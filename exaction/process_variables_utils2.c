/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_variables_utils2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahaded <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 04:03:23 by aahaded           #+#    #+#             */
/*   Updated: 2025/03/07 04:03:24 by aahaded          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid_char(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0'
			&& c <= '9') || c == '_')
		return (1);
	return (0);
}

void	copy_string(char *str, char *res)
{
	int	i;
	int	j;

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

int	calculate_length_(char *str)
{
	int	len;
	int	i;

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

void	remove_extra_spaces(char *env_var)
{
	int		j;
	int		i;
	char	*tmp;

	j = 0;
	i = 0;
	tmp = ft_malloc(ft_strlen(env_var) + 1);
	while (env_var && env_var[i])
	{
		if (env_var[i] == ' ')
		{
			tmp[j++] = env_var[i];
			while (env_var[i] && env_var[i] == ' ')
				i++;
		}
		if (env_var[i] && env_var[i] != ' ')
			tmp[j++] = env_var[i];
		i++;
	}
	tmp[j] = '\0';
	env_var = ft_strdup(tmp);
}
