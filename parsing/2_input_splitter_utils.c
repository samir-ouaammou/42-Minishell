#include "../minishell.h"

int	ft_check_input_is_valid(t_parsing *shell)
{
	if (!shell || !shell->input)
		return (0);
	shell->i = 0;
	while (shell->input && shell->input[shell->i])
	{
		if (shell->input[shell->i] != ' '
			&& shell->input[shell->i] != '\t'
			&& shell->input[shell->i] != '\n')
			break ;
		shell->i++;
	}
	shell->len = ft_strlen(shell->input);   
	if (shell->len != shell->i)
	{
		shell->i = 0;
		shell->len = 0;
		return (1);
	}
	shell->i = 0;
	while (shell->input && shell->input[shell->i])
	{
		if (shell->input[shell->i] == '\t')
			shell->input[shell->i] = ' ';
		shell->i++;
	}
	return (0);
}

int	ft_check_single_operators(t_parsing *shell)
{
	if ((shell->input[shell->i]) && (shell->input[shell->i] == '|'
			|| shell->input[shell->i] == '<' || shell->input[shell->i] == '>'
			|| shell->input[shell->i] == '(' || shell->input[shell->i] == ')'
			|| shell->input[shell->i] == '~' || shell->input[shell->i] == ':'
			|| shell->input[shell->i] == '#' || shell->input[shell->i] == '&'))
		return (1);
	return (0);
}

int	ft_check_double_operators(t_parsing *shell)
{
	if ((shell->input[shell->i] && shell->input[shell->i + 1])
		&& ((shell->input[shell->i] == '|' && shell->input[shell->i + 1] == '|')
			|| (shell->input[shell->i] == '&' && shell->input
				[shell->i + 1] == '&') || (shell->input[shell->i] == '>'
				&& shell->input[shell->i + 1] == '>')
			|| (shell->input[shell->i] == '<' && shell->input[shell->i + 1] == '<')))
		return (1);
	return (0);
}

void	ft_skip_string(t_parsing *shell)
{
	shell->chr = shell->input[shell->i];
	while (shell->input[shell->i])
	{
		shell->i++;
		shell->len++;
		if ((shell->input[shell->i]) && (shell->input[shell->i] == shell->chr))
			return ;
	}
	ft_free_args(shell);
}

void	ft_count_len_args(t_parsing *shell)
{
	shell->i = 0;
	shell->len = 0;
	while (shell->input && shell->input[shell->i])
	{
		if (shell->input[shell->i] == 34 || shell->input[shell->i] == 39)
		{
			if (shell->input[shell->i] && shell->input[shell->i + 1])
				ft_skip_string(shell);
			else
				ft_free_args(shell);
		}
		else if (ft_check_double_operators(shell))
		{
			shell->i++;
			shell->len += 3;
		}
		else if (ft_check_single_operators(shell))
			shell->len += 2;
		if (shell->input[shell->i])
			shell->i++;
		shell->len++;
	}
}


