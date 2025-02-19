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

char	*find_str_env(char *str, t_data *data)
{
	int	i;

	if (!str || !data->env)
		return (NULL);
	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], str, ft_strlen(str)) == 0)
			return (data->env[i]);
		i++;
	}
	return (NULL);
}

void	exaction(t_ast *root, t_data *data)
{
	execute_ast(root, data);
	// ft_printf("exit_status: %d\n", data->exit_status);
}
