/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaammo <souaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:06:26 by aahaded           #+#    #+#             */
/*   Updated: 2025/03/03 12:19:54 by souaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int is_numeric(const char *str)
{
	int i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int handle_exit_args(char **args, int *exit_code, t_exaction *data)
{
	if (args[1])
	{
		*exit_code = ft_atoi(args[1]);
		if (is_numeric(args[1]) && args[2])
		{
			ft_printf("minishell: exit: too many arguments\n");
			data->exit_status = 1;
			return (1);
		}
		if (!is_numeric(args[1]))
		{
			ft_printf("minishell: exit: %s: numeric argument required\n",
					  args[1]);
			exit(2);
		}
	}
	return (0);
}

int builtin_exit(char **args, t_exaction *data)
{
	(void)data;
	int exit_code;

	exit_code = 0;
	if (!args)
		return (1);
	ft_printf("exit\n");
	exit_code = handle_exit_args(args, &exit_code, data);
	if (!exit_code)
	{
		int status = 0;
		if (args[1])
			status = ft_atoi(args[1]);
		else
			status = data->exit_status;
		if (!status)
			status = 0;
		exit(status);
	}
	return (0);
}
