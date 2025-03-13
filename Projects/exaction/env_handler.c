/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahaded <aahaded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:25:07 by aahaded           #+#    #+#             */
/*   Updated: 2025/03/03 13:53:40 by aahaded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

void	add_pwd_if_missing(t_exaction *data, int check_pwd, int index)
{
	char	buf[PATH_MAX];
	char	*path;

	path = NULL;
	if (!check_pwd)
	{
		path = getcwd(buf, sizeof(buf));
		if (!path)
		{
			perror("minishell: getcwd");
			return ;
		}
		data->env[index] = ft_strjoin("PWD=", path);
	}
}

static void	copy_envp(char **envp, t_exaction *data)
{
	int	check_pwd;
	int	count;
	int	i;

	count = 0;
	check_pwd = check_pwd_exists(envp);
	while (envp[count])
		count++;
	if (!check_pwd)
		count++;
	data->env = ft_malloc(sizeof(char *) * (count + 1));
	if (!data->env)
	{
		perror("minishell: malloc");
		return ;
	}
	i = -1;
	while (envp[++i])
		data->env[i] = ft_strdup(envp[i]);
	add_pwd_if_missing(data, check_pwd, i);
	data->env[count] = NULL;
	initialize_and_copy_env_to_export(data);
	update_shlvl(data);
}

static void	initialize_environment_variables(t_exaction *data, int add_num,
		char *pwd_path_export)
{
	char	*str_j;

	data->export = ft_malloc(sizeof(char *) * (2 + add_num + 1));
	if (!data->export)
	{
		perror("Minishell: malloc");
		return ;
	}
	data->export[0] = ft_strdup("OLDPWD");
	if (add_num)
	{
		str_j = ft_strjoin("PWD=", pwd_path_export);
		if (str_j)
			pwd_path_export = add_double_quotes(str_j);
		data->export[add_num] = pwd_path_export;
	}
	data->export[add_num + 1] = ft_strdup(add_double_quotes("SHLVL=1"));
	data->export[add_num + 2] = NULL;
}

static void	create_default_env_export(t_exaction *data)
{
	int		add_num;
	char	path[PATH_MAX];
	char	*pwd_path;

	pwd_path = getcwd(path, sizeof(path));
	if (pwd_path != NULL)
		add_num = 1;
	else
		add_num = 0;
	if (!pwd_path)
	{
		perror("minishell: pwd");
		return ;
	}
	data->env = ft_malloc(sizeof(char *) * (1 + add_num + 1));
	if (!data->env)
	{
		perror("Minishell: malloc");
		return ;
	}
	if (add_num)
		data->env[0] = ft_strjoin("PWD=", pwd_path);
	data->env[add_num] = ft_strdup("SHLVL=1");
	data->env[add_num + 1] = NULL;
	initialize_environment_variables(data, add_num, pwd_path);
}

void	read_env(char **envp, t_exaction *data)
{
	if (*envp)
		copy_envp(envp, data);
	else
		create_default_env_export(data);
}
