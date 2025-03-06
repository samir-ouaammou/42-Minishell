/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exaction.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaammo <souaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:26:04 by aahaded           #+#    #+#             */
/*   Updated: 2025/03/03 13:53:40 by souaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *find_str_env(char *str, t_exaction *data)
{
	(void)data;
	int i;
	if (!str || !data_struc()->env || !data_struc()->env[0])
		return (NULL);
	i = 0;
	while (data_struc()->env[i])
	{
		if (ft_strncmp(data_struc()->env[i], str, ft_strlen(str)) == 0)
		{
			return (data_struc()->env[i]);
		}
		i++;
	}
	return (NULL);
}

void exaction(t_ast *root, t_exaction *data)
{
	// if (root == NULL)
	// 	return;
	// if (data_struc()->fd_file != -1)
	// {
	// 	close(data_struc()->fd_file);
	// 	data_struc()->fd_file = -1;
	// }
	// if (data_struc()->stdout_backup != -1)
	// {
	// 	close(data_struc()->stdout_backup);
	// 	data_struc()->stdout_backup = -1;
	// }
	// char *str = process_strings(root->value[0], data);
	// ft_printf("str: %s\n", str);
	// link_env_envBuffer(data);
	execute_ast(root, data);
	// data_struc()->check_file_1 = 0;
	// data_struc()->check_file_2 = 0;
	data_struc()->status = 0;
	data_struc()->fd_file = 0;
	// data_struc()->num_proess = 0;
	// data_struc()->num_proess2 = 0;
	// free_all(data_struc()->env);
	// free_all(data_struc()->matches);
	// free_all(data_struc()->DollarSign);
	// ft_printf("close 2\n");
	// ft_printf("exit_status: %d\n", data_struc()->exit_status);
}
