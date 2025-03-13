/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahaded <souaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 15:43:21 by aahaded           #+#    #+#             */
/*   Updated: 2025/03/06 23:35:10 by aahaded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	handle_newline_option(char **str, int *i)
{
	int	j;

	if (!str || !str[*i])
		return (1);
	j = 1;
	if (str[*i][0] == '-' && str[*i][1] == 'n')
	{
		while (str[*i][0] == '-' && str[*i][j] == 'n')
			j++;
		if (j == ft_strlen(str[*i]))
			return (0);
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

void	check_for_dollar_and_quotes(t_exaction *data, int j)
{
	int		dolar;
	int		k;
	char	c;

	dolar = 0;
	k = 0;
	while (data->copy[j][k])
	{
		if (data->copy[j][k] == 34 || data->copy[j][k] == 39)
		{
			c = data->copy[j][k++];
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
}

void	process_copy_with_quotes(t_exaction *data, char **str)
{
	int		j;
	int		i;
	char	**arg;

	j = 0;
	i = 0;
	while (data->copy && data->copy[j])
	{
		check_for_dollar_and_quotes(data, j);
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
}

int	builtin_echo(char **str, t_exaction *data)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (!str || !str[0])
		return (1);
	process_copy_with_quotes(data, str);
	if (str[1] && str[1][0] == '-' && str[1][1] == 'n')
		newline = handle_newline_option(str, &i);
	if (str[1] && str[1][0] == '-' && str[1][1] == 'n')
	{
		while (!newline && str[i] && str[i][0] == '-' && str[i][1] == 'n')
		{
			newline = handle_newline_option(str, &i);
			i++;
		}
		newline = 0;
	}
	print_arguments(str, i);
	if (newline)
		write(1, "\n", 1);
	data_struc()->exit_status = 0;
	return (0);
}
