/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exaction_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahaded <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 01:50:30 by aahaded           #+#    #+#             */
/*   Updated: 2025/03/07 01:50:31 by aahaded          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

char	*find_str_env(char *str, t_exaction *data)
{
	int	i;

	if (!str || !data->env || !data->env[0])
		return (NULL);
	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], str, ft_strlen(str)) == 0)
			return (data->env[i]);
		i++;
	}
	return (NULL);
}

void	check_shlvl(t_exaction *data)
{
	int		i;
	int		shlvl_value;
	char	*new_shlvl;

	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], "SHLVL=", 6) == 0)
		{
			shlvl_value = ft_atoi(data->env[i] + 6) + 1;
			if (shlvl_value > 1000 || shlvl_value <= 0)
			{
				new_shlvl = ft_strjoin("SHLVL=", "0");
				data->env[i] = new_shlvl;
			}
			return ;
		}
		i++;
	}
}
