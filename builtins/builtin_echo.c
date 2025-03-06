/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaammo <souaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 15:43:21 by aahaded           #+#    #+#             */
/*   Updated: 2025/03/06 23:35:10 by souaammo         ###   ########.fr       */
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

static void	print_arguments(t_exaction *data, char **str, int i)
{
	// int	j;
	// int	k;
	// int	dolar;
	// int	qouts;
(void)data;
	while (str[i])
	{
		// j = 0;
		// dolar = 0;
		// qouts = 0;
		// if (data->copy && data->copy[i])
		// {
		// 	k = 0;
		// }
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
	char	**arg;


	int j , k, dolar;
	j = 0;
	i = 0;
	while (data->copy && data->copy[j])
	{
		k = 0;
		dolar = 0;
		while (data->copy[j][k])
		{
			if (data->copy[j][k] == 34 || data->copy[j][k] == 39)
			{
				char c = data->copy[j][k++];
				while (data->copy[j][k] && data->copy[j][k] != c)
					k++;
			}
			if (data->copy[j][k] == '$')
				dolar = 1;
			k++;
		}
		if (dolar)
			data->space = 1;
		else
			data->space = 0;
		arg = ft_malloc(2 * sizeof(char *));
		arg[0] = ft_strdup(data->copy[j]);
		arg[1] = NULL;
		ft_remove_quots(arg, data, 1);
		str[i] = ft_strdup(arg[0]);
		j++;
		i++;
		arg = NULL;
	}
	str[i] = NULL;
	if (!str || !str[0])
		return (1);
	i = 1;
	newline = 1;
	if (str[1] && str[1][0] == '-' && str[1][1] == 'n')
		newline = handle_newline_option(str, &i);
	print_arguments(data, str, i);
	if (newline)
		write(1, "\n", 1);
	return (0);
}
