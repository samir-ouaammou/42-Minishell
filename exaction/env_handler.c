/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaammo <souaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:25:07 by aahaded           #+#    #+#             */
/*   Updated: 2025/03/03 13:53:40 by souaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void copy_envp(char **envp)
{
	int count, i;

	count = 0;
	while (envp[count])
		count++;
	data_struc()->env = ft_malloc(sizeof(char *) * (count + 1));
	if (!data_struc()->env)
		return;
	i = 0;
	while (envp[i])
	{
		data_struc()->env[i] = ft_strdup(envp[i]);
		if (!data_struc()->env[i])
		{
			free_all(data_struc()->env);
			data_struc()->env = NULL;
			return;
		}
		i++;
	}
	data_struc()->env[count] = NULL;
	// export ----------------------
	i = 0;
	count = 0;
	while (data_struc()->env[count])
		count++;
	data_struc()->export = ft_malloc(sizeof(char *) * (count + 1));
	if (!data_struc()->export)
		return;
	while (data_struc()->env[i])
	{
		data_struc()->export[i] = ft_strdup(data_struc()->env[i]);
		if (!data_struc()->export[i])
		{
			free_all(data_struc()->export);
			data_struc()->export = NULL;
			return;
		}
		i++;
	}
	data_struc()->export[count] = NULL;
	update_shlvl();
}

static void create_default_env()
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
		perror("minishell: pwd");
		return;
	}
	data_struc()->env = ft_malloc(sizeof(char *) * (2 + add_num + 1));
	if (!data_struc()->env)
	{
		perror("Minishell: malloc");
		return;
	}
	if (add_num)
		data_struc()->env[0] = ft_strjoin("PWD=", pwd_path);
	data_struc()->env[add_num] = ft_strdup("SHLVL=1");
	data_struc()->env[add_num + 1] = ft_strdup("_=/usr/bin/env");
	data_struc()->env[add_num + 2] = NULL;
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
		perror("minishell: pwd");
		return;
	}
	data_struc()->export = ft_malloc(sizeof(char *) * (2 + add_num + 1));
	if (!data_struc()->export)
	{
		perror("Minishell: malloc");
		return;
	}
	data_struc()->export[0] = ft_strdup("OLDPWD");
	if (add_num)
	{
		char *str_j = ft_strjoin("PWD=", pwd_path_export);
		pwd_path_export = add_double_quotes(str_j);
		data_struc()->export[add_num] = pwd_path_export;
	}
	data_struc()->export[add_num + 1] = ft_strdup(add_double_quotes("SHLVL=1"));
	data_struc()->export[add_num + 2] = NULL;
}

void read_env(char **envp)
{
	if (*envp)
		copy_envp(envp);
	else
		create_default_env();
}
