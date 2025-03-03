/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaammo <souaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 15:43:21 by aahaded           #+#    #+#             */
/*   Updated: 2025/03/03 12:19:54 by souaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	handle_newline_option(char **str, int *i)
{
	size_t	j;

	j = 1;
	if (str[1][0] == '-' && str[1][1] == 'n')
	{
		while (str[1][0] == '-' && str[1][j] == 'n')
			j++;
		if (j == ft_strlen(str[1]))
		{
			*i = 2;
			return (0);
		}
	}
	return (1);
}

static void	print_arguments(char **str, int i)
{
	while (str[i])
	{
		ft_putstr_fd(str[i], 1);
		if (str[i + 1])
			write(1, " ", 1);
		i++;
	}
}

int	builtin_echo(char **str, t_exaction *data)
{
	int	i;
	int	newline;

	(void)data;
	if (!str || !str[0])
		return (1);
	i = 1;
	newline = 1;
	if (str[1] && str[1][0] == '-' && str[1][1] == 'n')
		newline = handle_newline_option(str, &i);
	print_arguments(str, i);
	if (newline)
		write(1, "\n", 1);
	return (0);
}
