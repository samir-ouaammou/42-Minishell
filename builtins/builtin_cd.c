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

static void	update_prompt(t_exaction *data)
{
	char	*last_slash;
	char	*new_prompt;
	char	buffer[PATH_MAX];

	getcwd(buffer, sizeof(buffer));
	last_slash = ft_strrchr(buffer, '/');
	if (last_slash[0] == '/' && last_slash[1] != '\0')
	{
		new_prompt = ft_strjoin("➜ ", last_slash + 1);
		new_prompt = ft_strjoin(new_prompt, " ");
		data->name_pro = new_prompt;
	}
	else
		data->name_pro = "➜ / ";
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
	update_prompt(data);
	data_struc()->exit_status = 0;
	return (0);
}
