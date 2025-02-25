/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exaction.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahaded <aahaded@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:26:04 by aahaded           #+#    #+#             */
/*   Updated: 2025/02/17 16:26:08 by aahaded          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *find_str_env(char *str, t_data *data)
{
	int i;
	if (!str || !data->env || !data->env[0])
		return (NULL);
	i = 0;
			// printf("str: %s, env: %s\n", str, data->env[0]);
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], str, ft_strlen(str)) == 0)
		{
			return (data->env[i]);
		}
		i++;
	}
	return (NULL);
}

void exaction(t_ast *root, t_data *data)
{
	// if (root == NULL)
	// 	return;
	// if (data->fd_file != -1)
	// {
	// 	close(data->fd_file);
	// 	data->fd_file = -1;
	// }
	// if (data->stdout_backup != -1)
	// {
	// 	close(data->stdout_backup);
	// 	data->stdout_backup = -1;
	// }
	// char *str = process_template_string(root->value[0], data);
	// ft_printf("str: %s\n", str);
	execute_ast(root, data);
	data->check_file_1 = 0;
	data->check_file_2 = 0;
	data->status = 0;
	// free_all(data->env);
	// free_all(data->matches);
	// free_all(data->DollarSign);
	// ft_printf("close 2\n");
	// ft_printf("exit_status: %d\n", data->exit_status);
}
