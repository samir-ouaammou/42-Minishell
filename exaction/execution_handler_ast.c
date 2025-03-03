/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_handler_ast.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahaded <aahaded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:27:02 by aahaded           #+#    #+#             */
/*   Updated: 2025/02/25 14:19:58 by aahaded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int execute_builtin(char **args, t_data *data)
{
	if (ft_strcmp(args[0], "pwd") == 0)
		return (builtin_pwd(data));
	else if (ft_strcmp(args[0], "echo") == 0)
		return (builtin_echo(args, data));
	else if (ft_strcmp(args[0], "unset") == 0)
		return (builtin_unset(args, data));
	else if (ft_strcmp(args[0], "export") == 0)
		return (builtin_export(args, data));
	else if (ft_strcmp(args[0], "cd") == 0)
		return (builtin_cd(args, data));
	else if (ft_strcmp(args[0], "env") == 0)
		return (builtin_env(args, data));
	else if (ft_strcmp(args[0], "exit") == 0)
		return (builtin_exit(args, data));
	return (0);
}

static void handle_operator(t_ast *root, t_data *data)
{
	// ft_printf("lsssss\n");
	if (ft_strcmp(root->value[0], "&&") == 0)
	{
		execute_ast(root->left, data);
		if (data->status == 0)
			execute_ast(root->right, data);
	}
	else if (ft_strcmp(root->value[0], "||") == 0)
	{
		execute_ast(root->left, data);
		if (data->status != 0)
			execute_ast(root->right, data);
	}
	else if (ft_strcmp(root->value[0], "|") == 0)
		execute_pipe(root, data);
	else if (ft_strcmp(root->value[0], ">") == 0
	|| ft_strcmp(root->value[0], "<") == 0
	|| ft_strcmp(root->value[0], ">>") == 0)
		data->status = execute_redirection(root, data);
	else if (ft_strcmp(root->value[0], "<<") == 0)
		data->status = execute_heredoc(root, data);
}

static int handle_builtin(t_ast *root, t_data *data)
{
	char path[1024];

	if (getcwd(path, sizeof(path)))
		data->save_pwd = ft_strdup(path);
	if (check_special_chars(root->value) == 1)
	{
		handle_wildcards(root->value, data);
		ft_remove_quots(root->value, data);
		return (execute_builtin(data->matches, data));
	}
	else
	{
		ft_remove_quots(root->value, data);
		return (execute_builtin(root->value, data));
	}
}

static int handle_command(t_ast *root, t_data *data)
{
	if (check_special_chars(root->value) == 1)
	{
		handle_wildcards(root->value, data);
		ft_remove_quots(data->matches, data);
		if (is_builtin(data->matches[0], data))
			data->status = handle_builtin(root, data);
		else
			data->status = execute_command(data->matches, data);
	}
	else
	{
		ft_remove_quots(root->value, data);
		data->status = execute_command(root->value, data);
	}
	return (data->status);
}

int execute_ast(t_ast *root, t_data *data)
{
	if (!root)
		return (FAILED);
	if (is_operator(root->value[0]))
		handle_operator(root, data);
	else if (is_builtin(root->value[0], data))
		data->status = handle_builtin(root, data);
	else
		data->status = handle_command(root, data);
	return (data->status);
}