/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahaded <aahaded@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:13:03 by aahaded           #+#    #+#             */
/*   Updated: 2025/02/16 18:13:05 by aahaded          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_pwd(void)
{
	char	path[1024];

	if (getcwd(path, sizeof(path)))
	{
		ft_printf("%s\n", path);
		return (0);
	}
	else
	{
		perror("minishell: pwd: error");
		return (1);
	}
}
