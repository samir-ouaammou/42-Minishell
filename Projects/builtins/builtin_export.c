/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahaded <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 22:04:17 by aahaded           #+#    #+#             */
/*   Updated: 2025/03/06 22:04:19 by aahaded          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parse_plus_and_equals(char **args, int index, t_exaction *data)
{
	int	j;

	j = 0;
	while (args[index][j])
	{
		if (args[index][j] == '+')
			data->is_plus = 1;
		if (args[index][j] == '=')
			break ;
		j++;
	}
}

int	validate_export_argument(char **args, int index)
{
	int		index_check;
	char	**split_str;
	int		check_error;

	check_error = 0;
	split_str = ft_split(args[index], '=');
	index_check = check_plus(args[index]);
	if (args[index][0] == '=' || index_check
		|| is_valid_export_identifier(split_str[0]) == 1)
	{
		ft_printf("minishell: export: `%s': not a valid identifier\n",
			args[index]);
		check_error = 1;
		data_struc()->exit_status = 1;
	}
	return (check_error);
}

void	process_export_argument(t_exaction *data, char **args, int index,
		char *str)
{
	int	found;
	int	found_export;

	found = 0;
	found_export = 0;
	parse_plus_and_equals(args, index, data);
	if (data->is_plus == 1)
		handle_plus_operator(index, args);
	found = update_env_var(args, data, str, index);
	found_export = update_export_var(args, data, str, index);
	if (!found)
		add_new_env_var(args, data, index);
	if (!found_export)
	{
		args[index] = add_double_quotes(args[index]);
		add_new_export_var(args, data, index);
	}
}

void	handle_export_arguments(t_exaction *data, char **args, int index,
		int *check_s)
{
	char	*str;

	str = NULL;
	while (args[index])
	{
		if (validate_export_argument(args, index) || (args[index][0] == '_'
			&& args[index][1] == '='))
		{
			(*check_s) = 1;
			index++;
			continue ;
		}
		str = ft_strchr(args[index], '=');
		if (str)
			process_export_argument(data, args, index, str);
		else
			add_default_export(args[index], data, (ft_strlen(args[index])
					- ft_strlen(str)));
		index++;
	}
}

int	builtin_export(char **args, t_exaction *data)
{
	int	i;
	int	check_s;

	i = 1;
	check_s = 0;
	data->is_plus = 0;
	if (!args || !data || !data->env || !data->export)
		return (1);
	if (!args[1])
		print_export(data);
	else
		handle_export_arguments(data, args, i, &check_s);
	if (!check_s)
		data_struc()->exit_status = 0;
	return (0);
}
