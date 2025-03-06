/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exaction.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaammo <souaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:26:04 by aahaded           #+#    #+#             */
/*   Updated: 2025/03/03 13:53:40 by souaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *find_str_env(char *str, t_exaction *data)
{
	(void)data;
	int i;
	if (!str || !data_struc()->env || !data_struc()->env[0])
		return (NULL);
	i = 0;
	while (data_struc()->env[i])
	{
		if (ft_strncmp(data_struc()->env[i], str, ft_strlen(str)) == 0)
			return (data_struc()->env[i]);
		i++;
	}
	return (NULL);
}

void update_shlvl()
{
	int i;
	int shlvl_value;
	char *new_shlvl;

	i = 0;
	while (data_struc()->env[i])
	{
		if (ft_strncmp(data_struc()->env[i], "SHLVL=", 6) == 0)
		{
			shlvl_value = ft_atoi(data_struc()->env[i] + 6) + 1;
			if (shlvl_value >= 1000)
				shlvl_value = 0;
			else if (shlvl_value <= 0)
				shlvl_value = 0;
			char *num = ft_itoa(shlvl_value);
			new_shlvl = ft_strjoin("SHLVL=", num);
			data_struc()->env[i] = new_shlvl;
			return;
		}
		i++;
	}
}

void exaction(t_ast *root, t_exaction *data)
{
	execute_ast(root, data);
	data_struc()->status = 0;
}
