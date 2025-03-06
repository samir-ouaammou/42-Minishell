/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaammo <souaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:05:25 by aahaded           #+#    #+#             */
/*   Updated: 2025/03/03 12:19:54 by souaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

int builtin_env(char **args, t_exaction *data)
{
	int i;

	if (!data || !data_struc()->env || !args)
		return (-1);
	else if (args && args[1])
	{
		ft_printf("minishell: env: too many arguments\n");
		data_struc()->exit_status = 1;
	}
	else
	{
		i = 0;
		while (data_struc()->env[i])
		{
			printf("%s\n", data_struc()->env[i]);
			i++;
		}
	}
	return (0);
}
