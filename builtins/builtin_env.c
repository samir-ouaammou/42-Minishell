/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahaded <aahaded@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:05:25 by aahaded           #+#    #+#             */
/*   Updated: 2025/02/16 18:05:29 by aahaded          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_env(char **args, t_data *data)
{
	int	i;

	if (!data || !data->env || !args)
		return (-1);
	else if (args && args[1])
		write(2, "minishell: env: too many arguments\n", 35);
	else
	{
		i = 0;
		while (data->env[i])
		{
			ft_printf("%s\n", data->env[i]);
			i++;
		}
	}
	return (0);
}
