#include "../minishell.h"

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

void	exaction(t_ast *root, t_data *data)
{
	execute_ast(root, data);
}
