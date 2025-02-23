/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_operator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaammo <souaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 08:16:41 by aahaded           #+#    #+#             */
/*   Updated: 2025/02/23 17:14:45 by souaammo         ###   ########.fr       */
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

int	is_builtin(char *cmd)
{
	return (ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "env") == 0 || ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "export") == 0 || ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "exit") == 0);
}
