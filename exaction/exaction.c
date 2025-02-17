#include "../minishell.h"

int				execute_ast(t_ast *root, t_data *data);



//---------------------------------------
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
	return (0);
}

int	count_args_value(t_ast *node, char *type)
{
	int	count;

	count = 0;
	if (ft_strcmp(type, "left") == 0)
	{
		while (node->left->value[count])
			count++;
	}
	else if (ft_strcmp(type, "right") == 0)
	{
		while (node->right->value[count])
			count++;
	}
	return (count);
}


void	ft_strcpy(char *dest, char *src)
{
	while ((*dest++ = *src++))
		;
}
//------------------------------------------------------
static int	calculate_length2(char *str)
{
	int(len), (i);
	len = 0;
	i = 1;
	while (str[i])
	{
		if (str[i] != '$')
			len++;
		i++;
	}
	return (len);
}

static void	copy_string(char *str, char *res)
{
	int(i), (j);
	i = 1;
	j = 0;
	while (str[i])
	{
		if (str[i] != '$')
			res[j++] = str[i];
		else
			break ;
		i++;
	}
	res[j] = '\0';
}

static char	*get_str_Dollars(char *str)
{
	int		len;
	char	*res;

	len = calculate_length2(str);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	copy_string(str, res);
	return (res);
}

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

static size_t	handle_env_var_length(char *str, t_data *data, int *index)
{
	size_t	len;
	char	*var;
	char	*env_var;
	char	*chrstr;

	len = 0;
	var = get_str_Dollars(&str[*index]);
	if (var)
	{
		len += ft_strlen(var);
		env_var = find_str_env(ft_strjoin(var, "="), data);
		if (env_var)
		{
			chrstr = ft_strchr(env_var, '=');
			if (chrstr)
				len += ft_strlen(chrstr) - 1;
		}
		*index += ft_strlen(var) + 1;
	}
	return (len);
}

static size_t	handle_exit_status_length(t_data *data, int *index)
{
	size_t	len;
	char	*exit_status;

	len = 0;
	exit_status = ft_itoa(data->exit_status);
	if (exit_status)
	{
		len += ft_strlen(exit_status);
		free(exit_status);
	}
	*index += 2;
	return (len);
}

static size_t	calculate_length(char *str, t_data *data)
{
	size_t	len;
	int		index;

	len = 0;
	index = 0;
	while (str[index])
	{
		if (str[index] == '$' && str[index + 1] != '?')
			len += handle_env_var_length(str, data, &index);
		else if (str[index] == '$' && str[index + 1] == '?')
			len += handle_exit_status_length(data, &index);
		else
		{
			len++;
			index++;
		}
	}
	return (len);
}

static void	handle_env_var(char *str, char *res, t_data *data, int *res_index)
{
	char(*var), (*chrstr), (*env_var);
	var = get_str_Dollars(str);
	if (var)
	{
		env_var = find_str_env(ft_strjoin(var, "="), data);
		if (env_var)
		{
			chrstr = ft_strchr(env_var, '=');
			if (chrstr)
			{
				ft_strcpy(&res[*res_index], chrstr + 1);
				*res_index += ft_strlen(chrstr) - 1;
			}
		}
	}
}

static void	handle_exit_status(char *res, t_data *data, int *res_index)
{
	char	*exit_status;

	exit_status = ft_itoa(data->exit_status);
	if (exit_status)
	{
		ft_strcpy(&res[*res_index], exit_status);
		*res_index += ft_strlen(exit_status);
	}
}

static void	process_variable(char *str, char *res, t_data *data, int *res_index)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != '?')
		{
			handle_env_var(&str[i], res, data, res_index);
			i += ft_strlen(get_str_Dollars(&str[i])) + 1;
		}
		else if (str[i] == '$' && str[i + 1] == '?')
		{
			handle_exit_status(res, data, res_index);
			i += 2;
		}
		else
		{
			res[*res_index] = str[i];
			(*res_index)++;
			i++;
		}
	}
	res[*res_index] = '\0';
}

void	process_strings(t_ast *root, t_data *data)
{
	char	**res;

	int(i), (count), (res_index);
	if (!root || !root->value || !data)
		return ;
	count = 0;
	while (root->value[count])
		count++;
	res = malloc(sizeof(char *) * (count + 1));
	if (!res)
		return ;
	i = 0;
	while (i < count)
	{
		res[i] = malloc(calculate_length(root->value[i], data) + 1);
		if (!res[i])
			return ;
		res_index = 0;
		process_variable(root->value[i], res[i], data, &res_index);
		i++;
	}
	res[count] = NULL;
	root->value = res;
}
//------------------------------------------------------
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

//------------------------------------------------------

static void	copy_envp(t_data *data, char **envp)
{
	int(count), (i);
	count = 0;
	while (envp[count])
		count++;
	data->env = malloc(sizeof(char *) * (count + 1));
	if (!data->env)
		return ;
	i = 0;
	while (envp[i])
	{
		data->env[i] = ft_strdup(envp[i]);
		if (!data->env[i])
		{
			data->env = NULL;
			return ;
		}
		i++;
	}
	data->env[count] = NULL;
}

static void	create_default_env(t_data *data)
{
	int	add_num;

	char(path[1024]), (*pwd_path);
	pwd_path = getcwd(path, sizeof(path));
	if (pwd_path != NULL)
		add_num = 1;
	else
		add_num = 0;
	if (!pwd_path)
	{
		perror("minishell: pwd: error");
		return ;
	}
	data->env = malloc(sizeof(char *) * (2 + add_num + 1));
	if (!data->env)
	{
		perror("Minishell: malloc");
		return ;
	}
	if (add_num)
		data->env[0] = ft_strjoin("PATH=", pwd_path);
	data->env[add_num] = ft_strdup("SHLVL=1");
	data->env[add_num + 1] = ft_strdup("_=/usr/bin/env");
	data->env[add_num + 2] = NULL;
}

void	read_env(t_data *data, char **envp)
{
	if (*envp)
		copy_envp(data, envp);
	else
		create_default_env(data);
}

void	exaction(t_ast *root, t_data *data)
{
	data->err_status = 0;
	execute_ast(root, data);
}
