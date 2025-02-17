#include "../minishell.h"

static int	check_special_chars(char **args)
{
	int(i), (j);
	i = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (args[i][j] == '$' && args[i][j + 1] == '\0')
				return (0);
			else if (args[i][j] == '*')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static int	execute_builtin(t_ast *root, t_data *data)
{
	if (ft_strcmp(root->value[0], "pwd") == 0)
		return (builtin_pwd());
	else if (ft_strcmp(root->value[0], "echo") == 0)
		return (builtin_echo(root->value, data));
	else if (ft_strcmp(root->value[0], "unset") == 0)
		return (builtin_unset(root, data));
	else if (ft_strcmp(root->value[0], "export") == 0)
		return (builtin_export(root, data));
	else if (ft_strcmp(root->value[0], "cd") == 0)
		return (builtin_cd(root->value, data));
	else if (ft_strcmp(root->value[0], "env") == 0)
		return (builtin_env(root->value, data));
	else if (ft_strcmp(root->value[0], "exit") == 0)
		return (builtin_exit(root, data));
	return (0);
}

static void	handle_operator(t_ast *root, t_data *data)
{
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
	else if (ft_strcmp(root->value[0], ">") == 0)
		execute_redir_RightArrow_redirout(root, data, "redirout");
	else if (ft_strcmp(root->value[0], "<") == 0)
		execute_redir_inp(root, data);
	else if (ft_strcmp(root->value[0], ">>") == 0)
		execute_redir_RightArrow_redirout(root, data, "RightArrow");
}

static int	handle_builtin(t_ast *root, t_data *data)
{
	ft_remove_quots(root->value);
    process_strings(root, data);
	return (execute_builtin(root, data));
}

static int	handle_command(t_ast *root, t_data *data)
{
	if (check_special_chars(root->value) == 1)
	{
		handle_wildcards(root->value, data);
		ft_remove_quots(root->value);
        process_strings(root, data);
		data->status = execute_command(data->matches, data);
	}
	else
	{
		ft_remove_quots(root->value);
        process_strings(root, data);
		data->status = execute_command(root->value, data);
	}
	return (data->status);
}

int	execute_ast(t_ast *root, t_data *data)
{
	if (!root)
		return (FAILED);
	
	if (is_operator(root->value[0]))
		handle_operator(root, data);
	else if (is_builtin(root->value[0]))
		data->status = handle_builtin(root, data);
	else
		data->status = handle_command(root, data);
	return (data->status);
}