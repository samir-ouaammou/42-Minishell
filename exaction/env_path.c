/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahaded <aahaded@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 08:20:01 by aahaded           #+#    #+#             */
/*   Updated: 2025/02/17 08:20:04 by aahaded          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_path_env_utils(char **path, char *cmd)
{
	char	*path_arg;
	int		i;

	i = 0;
	while (path[i])
	{
		path_arg = ft_strjoin(path[i], "/");
		path_arg = ft_strjoin(path_arg, cmd);
		if (access(path_arg, X_OK) == 0)
			return (path_arg);
		i++;
	}
	return (NULL);
}

char	*get_path_env(char *cmd, t_data *data)
{
	char	**path;

	int(i), (check_path);
	i = 0;
	check_path = 0;
	path = NULL;
	if (!data->env)
		return (NULL);
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], "PATH=", 5) == 0)
		{
			check_path = 1;
			path = ft_split(data->env[i] + 5, ':');
			break ;
		}
		i++;
	}
	if (!check_path)
		return (NULL);
	else if (cmd == NULL || is_operator(cmd))
		return (NULL);
	else if (get_path_env_utils(path, cmd))
		return (get_path_env_utils(path, cmd));
	return (NULL);
}
