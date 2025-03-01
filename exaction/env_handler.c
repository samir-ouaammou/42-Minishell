/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahaded <aahaded@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:25:07 by aahaded           #+#    #+#             */
/*   Updated: 2025/02/17 16:25:09 by aahaded          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void update_shlvl(t_data *data)
{
	int i;
	int shlvl_value;
	char *new_shlvl;

	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], "SHLVL=", 6) == 0)
		{
			shlvl_value = ft_atoi(data->env[i] + 6) + 1;
			new_shlvl = ft_strjoin("SHLVL=", ft_itoa(shlvl_value));
			// free(data->env[i]);
			data->env[i] = new_shlvl;
			return;
		}
		i++;
	}
}

static void copy_envp(t_data *data, char **envp)
{
	int count, i;

	count = 0;
	while (envp[count])
		count++;
	data->env = malloc(sizeof(char *) * (count + 1));
	if (!data->env)
		return;
	i = 0;
	while (envp[i])
	{
		data->env[i] = ft_strdup(envp[i]);
		if (!data->env[i])
		{
			// free_all(data->env);
			data->env = NULL;
			return;
		}
		i++;
	}
	data->env[count] = NULL;
	// export ----------------------
	i = 0;
	count = 0;
	while (data->env[count])
		count++;
	data->export = malloc(sizeof(char *) * (count + 1));
	if (!data->export)
		return;
	while (data->env[i])
	{
		data->export[i] = ft_strdup(data->env[i]);
		if (!data->export[i])
		{
			// free_all(data->env);
			data->export = NULL;
			return;
		}
		i++;
	}
	data->export[count] = NULL;
	update_shlvl(data);
}

static void create_default_env(t_data *data)
{
	int add_num;
	char path[1024], (*pwd_path);

	pwd_path = getcwd(path, sizeof(path));
	if (pwd_path != NULL)
		add_num = 1;
	else
		add_num = 0;
	if (!pwd_path)
	{
		perror("minishell: pwd: error");
		return;
	}
	data->env = malloc(sizeof(char *) * (2 + add_num + 1));
	if (!data->env)
	{
		perror("Minishell: malloc");
		return;
	}
	if (add_num)
		data->env[0] = ft_strjoin("PWD=", pwd_path);
	data->env[add_num] = ft_strdup("SHLVL=1");
	data->env[add_num + 1] = ft_strdup("_=/usr/bin/env");
	data->env[add_num + 2] = NULL;
	// export ------------------------------------
	add_num = 0;
	char path_export[1024], (*pwd_path_export);

	pwd_path_export = getcwd(path_export, sizeof(path));
	if (pwd_path_export != NULL)
		add_num = 1;
	else
		add_num = 0;
	if (!pwd_path_export)
	{
		perror("minishell: pwd: error");
		return;
	}
	data->export = malloc(sizeof(char *) * (2 + add_num + 1));
	if (!data->export)
	{
		perror("Minishell: malloc");
		return;
	}
	data->export[0] = ft_strdup("OLDPWD");
	if (add_num)
	{
		char *str_j = ft_strjoin("PWD=", pwd_path_export);
		pwd_path_export = add_double_quotes(str_j);
		free(str_j);
		data->export[add_num] = pwd_path_export;
	}
	data->export[add_num + 1] = ft_strdup(add_double_quotes("SHLVL=1"));
	data->export[add_num + 2] = NULL;
}

void read_env(t_data *data, char **envp)
{
	if (*envp)
		copy_envp(data, envp);
	else
		create_default_env(data);
}
