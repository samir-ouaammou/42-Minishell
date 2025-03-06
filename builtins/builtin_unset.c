/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaammo <souaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:13:36 by aahaded           #+#    #+#             */
/*   Updated: 2025/03/03 12:19:54 by souaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


static void	remove_env_var(t_exaction *data, int index)
{
	(void)data;
	while (data_struc()->env[index + 1])
	{
		data_struc()->env[index] = data_struc()->env[index + 1];
		index++;
	}
	data_struc()->env[index] = NULL;
}

static void	remove_export_var(t_exaction *data, int index)
{
	(void)data;
	while (data_struc()->export[index + 1])
	{
		data_struc()->export[index] = data_struc()->export[index + 1];
		index++;
	}
	data_struc()->export[index] = NULL;
}

int	builtin_unset(char **args, t_exaction *data)
{
	(void)data;
	int	i;
	int	j;

	if (!args || !data || !data_struc()->env || !data_struc()->export)
	{
		data_struc()->exit_status = 1;
		return (1);
	}
	i = 1;
	while (args[i])
	{
		j = 0;
		while (data_struc()->env[j])
		{
			if (ft_strncmp(args[i], data_struc()->env[j],
					ft_strlen(args[i])) == 0)
			{
				remove_env_var(data, j);
				break ;
			}
			j++;
		}
		j = 0;
		while (data_struc()->export[j])
		{
			if (ft_strncmp(args[i], data_struc()->export[j],
					ft_strlen(args[i])) == 0)
			{
				remove_export_var(data, j);
				break ;
			}
			j++;
		}
		i++;
	}
	return (0);
}
