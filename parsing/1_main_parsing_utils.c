#include "../minishell.h"

static int	ft_calculate_new_length(t_parsing *shell, char *input)
{
	shell->i = 0;
	shell->len = 0;
	while (input[shell->i])
	{
		if (input[shell->i] == '\t')
			shell->len += 7;
		else
			shell->len += 1;
		shell->i++;
	}
	return (shell->len);
}

static void	ft_convert_tabs_to_spaces(t_parsing *shell, char *input)
{
	shell->i = 0;
	shell->j = 0;
	while (input[shell->i])
	{
		if (input[shell->i] == '\t')
		{
			shell->cmds[shell->j++] = ' ';
			shell->cmds[shell->j++] = ' ';
			shell->cmds[shell->j++] = ' ';
			shell->cmds[shell->j++] = ' ';
			shell->cmds[shell->j++] = ' ';
			shell->cmds[shell->j++] = ' ';
			shell->cmds[shell->j++] = ' ';
		}
		else
			shell->cmds[shell->j++] = input[shell->i];
		shell->i++;
	}
	shell->cmds[shell->j] = '\0';
}

void	ft_replace_tabs_with_spaces(t_parsing *shell, char *input)
{
	shell->len = ft_calculate_new_length(shell, input);
	shell->cmds = (char *)ft_malloc(shell->len + 1);
	if (!shell->cmds)
		return ;
	ft_convert_tabs_to_spaces(shell, input);
	shell->input = ft_strdup(shell->cmds);
	ft_init_parsing(shell);
}

void	ft_replace_newline_with_space(t_parsing *shell)
{
	if (!shell || !shell->input || !shell->input[0])
		return ;
	shell->i = 0;
	shell->j = 0;
	while (shell->input[shell->i])
	{
		if (shell->input[shell->i] == 34 || shell->input[shell->i] == 39)
		{
			shell->chr = shell->input[shell->i++];
			while (shell->input[shell->i]
				&& shell->input[shell->i] != shell->chr)
				shell->i++;
		}
		if (shell->input[shell->i] == '\n')
			shell->input[shell->i] = ' ';
		if (shell->input[shell->i])
			shell->i++;
	}
	ft_init_parsing(shell);
}
