/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahaded <aahaded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 08:20:01 by aahaded           #+#    #+#             */
/*   Updated: 2025/03/03 13:53:40 by aahaded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_path_env_utils(char **path, char *cmd)
{
	char	*temp;
	char	*path_arg;
	int		i;

	i = 0;
	while (path[i])
	{
		path_arg = ft_strjoin(path[i], "/");
		if (!path_arg)
			return (NULL);
		temp = ft_strjoin(path_arg, cmd);
		if (!temp)
			return (NULL);
		if (access(temp, X_OK) == 0)
			return (temp);
		i++;
	}
	return (NULL);
}

char	*get_path_env(char *cmd, t_exaction *data)
{
	char	**path;
	char	*path_arg;
	int		i;
	int		check_path;

	i = 0;
	check_path = 0;
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
	path_arg = get_path_env_utils(path, cmd);
	if (!path_arg)
		return (NULL);
	return (path_arg);
}
