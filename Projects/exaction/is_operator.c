/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_operator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahaded <aahaded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 08:16:41 by aahaded           #+#    #+#             */
/*   Updated: 2025/02/25 14:12:26 by aahaded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

int	is_operator(char *str)
{
	return (ft_strcmp(str, "|") == 0 || ft_strcmp(str, "||") == 0
		|| ft_strcmp(str, "&&") == 0 || ft_strcmp(str, ">") == 0
		|| ft_strcmp(str, "<") == 0 || ft_strcmp(str, "<<") == 0
		|| ft_strcmp(str, ">>") == 0);
}

int	is_builtin(char *cmd, t_exaction *data)
{
	char	**args;
	char	*temp;

	args = ft_malloc(sizeof(char *) * 2);
	if (!args)
		return (1);
	args[0] = ft_strdup(cmd);
	args[1] = NULL;
	ft_remove_quots(args, data, 1);
	temp = ft_strdup(args[0]);
	if (ft_strcmp(temp, "cd") == 0 || ft_strcmp(temp, "echo") == 0
		|| ft_strcmp(temp, "env") == 0 || ft_strcmp(temp, "pwd") == 0
		|| ft_strcmp(temp, "export") == 0 || ft_strcmp(temp, "unset") == 0
		|| ft_strcmp(temp, "exit") == 0)
		return (1);
	return (0);
}
