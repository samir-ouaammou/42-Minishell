/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exaction.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahaded <aahaded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:26:04 by aahaded           #+#    #+#             */
/*   Updated: 2025/03/03 13:53:40 by aahaded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_pwd_in_export(t_exaction *data, char *path)
{
	int		i;
	char	*str_j;

	i = 0;
	while (data->export[i])
	{
		if (ft_strncmp(data->export[i], "PWD=", 4) == 0)
		{
			str_j = ft_strjoin("PWD=", path);
			data->export[i] = str_j;
			break ;
		}
		i++;
	}
}

void	update_oldpwd_in_env(t_exaction *data)
{
	int		i;
	char	*str_j;

	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], "OLDPWD=", 7) == 0)
		{
			str_j = ft_strjoin("OLDPWD=", data->save_oldpwd);
			if (str_j)
				data->env[i] = str_j;
			break ;
		}
		i++;
	}
}

void	update_oldpwd_in_export(t_exaction *data)
{
	int		i;
	char	*str_j;

	i = 0;
	while (data->export[i])
	{
		if (ft_strncmp(data->export[i], "OLDPWD=", 7) == 0
			|| ft_strncmp(data->export[i], "OLDPWD", 6) == 0)
		{
			str_j = ft_strjoin("OLDPWD=", data->save_oldpwd);
			if (str_j)
				data->export[i] = str_j;
			break ;
		}
		i++;
	}
}

void	update_env_export(t_exaction *data)
{
	char	buf[PATH_MAX];
	char	*path;
	int		i;
	char	*str_j;

	path = getcwd(buf, sizeof(buf));
	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], "PWD=", 4) == 0)
		{
			str_j = ft_strjoin("PWD=", path);
			data->env[i] = str_j;
			break ;
		}
		i++;
	}
	update_pwd_in_export(data, path);
	update_oldpwd_in_env(data);
	update_oldpwd_in_export(data);
}

void	exaction(t_ast *root, t_exaction *data)
{
	execute_ast(root, data);
	update_env_export(data);
	check_shlvl(data);
	data->status = 0;
}
