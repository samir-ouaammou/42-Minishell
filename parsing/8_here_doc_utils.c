#include "../minishell.h"

void	ft_handle_redirect_content(t_parsing *shell, int *j, int *k)
{
	int	i;

	while (shell->tokens)
	{
		if (ft_check_is_operators(shell->tokens->value[0]))
			break ;
		i = 0;
		while (shell->tokens->value[i])
		{
			if (!(*k))
			{
				if (shell->tmp)
					shell->tmp = NULL;
				shell->tmp = ft_malloc((shell->tab[(*j)++] + 1)
						* sizeof(char *));
			}
			shell->tmp[*k] = ft_strdup(shell->tokens->value[i]);
			(*k)++;
			i++;
		}
		if (shell->tokens)
			shell->tokens = shell->tokens->next;
	}
	if (*k)
		shell->tmp[*k] = NULL;
}

void	process_tabs(t_parsing *shell, char *str)
{
	while (str[shell->i])
	{
		if (str[shell->i] == '\t')
		{
			shell->j++;
			while (str[shell->i] && str[shell->i] == '\t')
				shell->i++;
		}
		if (str[shell->i])
			shell->i++;
	}
}

void	allocate_memory(t_parsing *shell, char *str)
{
	shell->help = ft_malloc(ft_strlen(str) + (shell->j * 15) + 1);
	if (!shell->help)
		return ;
	shell->j = 0;
	shell->i = 0;
}

void	ft_move_input(t_parsing *shell, char *str)
{
	if (!shell || !str)
		return ;
	shell->i = 0;
	shell->j = 0;
	shell->nbr = 1;
	shell->help = NULL;
	process_tabs(shell, str);
	if (shell->j == 0)
		return ;
	allocate_memory(shell, str);
	if (!shell->help)
		return ;
	process_input(shell, str);
	shell->help[shell->j] = '\0';
	shell->input = ft_strdup(shell->help);
}

void	ft_init_here_doc(t_parsing *shell)
{
	shell->i = 0;
	shell->bol = 0;
	shell->nbr = 1;
	shell->start = 0;
	shell->end = 0;
	shell->stop = ft_malloc(sizeof(char *) * 2);
	if (!shell->stop)
		return ;
	shell->stop[1] = NULL;
}
