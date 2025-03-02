/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaammo <souaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:05:25 by aahaded           #+#    #+#             */
/*   Updated: 2025/03/02 16:13:32 by souaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

int builtin_env(char **args, t_data *data)
{
	int i;

	if (!data || !data->env || !args)
		return (-1);
	else if (args && args[1])
	{
		ft_printf("minishell: env: too many arguments\n");
		data->exit_status = 1;
	}
	else
	{
		i = 0;
		while (data->env[i])
		{
			printf("%s\n", data->env[i]);
			i++;
		}
	}
	return (0);
}
