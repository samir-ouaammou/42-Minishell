/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahaded <souaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 15:16:22 by aahaded           #+#    #+#             */
/*   Updated: 2025/03/03 12:19:54 by aahaded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

static int	handle_directory_change(char *dir)
{
	if (chdir(dir) == -1)
	{
		ft_printf("minishell: %s: %s\n", dir, strerror(errno));
		data_struc()->exit_status = 1;
		return (1);
	}
	return (0);
}

int	builtin_cd(char **args, t_exaction *data)
{
	char	buffer[PATH_MAX];

	if (getcwd(buffer, sizeof(buffer)))
		data->save_oldpwd = ft_strdup(buffer);
	if (args[2])
	{
		ft_printf("minishell: cd: too many arguments\n");
		data_struc()->exit_status = 1;
		return (1);
	}
	if (args[0] && !args[1])
	{
		ft_printf("minishell: cd: HOME not set\n");
		data_struc()->exit_status = 1;
		return (0);
	}
	if (handle_directory_change(args[1]) != 0)
		return (1);
	data_struc()->exit_status = 0;
	return (0);
}
