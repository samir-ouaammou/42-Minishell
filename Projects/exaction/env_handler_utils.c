/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahaded <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 00:57:28 by aahaded           #+#    #+#             */
/*   Updated: 2025/03/07 00:57:29 by aahaded          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

void	update_shlvl(t_exaction *data)
{
	int		i;
	int		shlvl_value;
	char	*new_shlvl;
	char	*num;

	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], "SHLVL=", 6) == 0)
		{
			shlvl_value = ft_atoi(data->env[i] + 6) + 1;
			if (shlvl_value > 1000 || shlvl_value <= 0)
			{
				new_shlvl = ft_strjoin("SHLVL=", "0");
				data->env[i] = new_shlvl;
				return ;
			}
			num = ft_itoa(shlvl_value);
			new_shlvl = ft_strjoin("SHLVL=", num);
			data->env[i] = new_shlvl;
			return ;
		}
		i++;
	}
}

char	*add_double_quotes_test(char *str)
{
	int		i;
	int		j;
	char	*res;

	res = ft_malloc(ft_strlen(str) + 500 + 1);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			res[j++] = str[i++];
			res[j++] = '"';
		}
		else
			res[j++] = str[i++];
	}
	res[j++] = '"';
	res[j] = '\0';
	return (res);
}

void	initialize_and_copy_env_to_export(t_exaction *data)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (data->env[count])
		count++;
	data->export = ft_malloc(sizeof(char *) * (count + 3));
	if (!data->export)
	{
		perror("minishell: malloc");
		return ;
	}
	data->export[0] = ft_strdup("OLDPWD");
	i = -1;
	while (data->env[++i])
		data->export[i + 1] = add_double_quotes(data->env[i]);
	data->export[count + 1] = NULL;
}

int	check_pwd_exists(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PWD=", 4) == 0)
			return (1);
		i++;
	}
	return (0);
}
