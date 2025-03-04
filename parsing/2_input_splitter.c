#include "../minishell.h"

void	ft_str_copy(t_parsing *shell)
{
	// shell->cmds[shell->len++] = '\t';
	shell->chr = shell->input[shell->i];
	while (shell->input[shell->i])
	{
		shell->cmds[shell->len++] = shell->input[shell->i++];
		if (shell->input[shell->i] == shell->chr)
		{
			shell->cmds[shell->len++] = shell->input[shell->i];
			// shell->cmds[shell->len++] = '\t';
			return ;
		}
	}
	ft_free_args(shell);
}

void	ft_this_condition_function(t_parsing *shell)
{
	if (shell->input[shell->i] == '~' || shell->input[shell->i] == '$')
	{
		shell->cmds[shell->len++] = '\t';
		shell->cmds[shell->len++] = '\t';
		shell->cmds[shell->len++] = shell->input[shell->i];
	}
	else if (shell->input[shell->i] == '=' || shell->input[shell->i] == ':')
	{
		shell->cmds[shell->len++] = shell->input[shell->i];
		shell->cmds[shell->len++] = '\t';
		shell->cmds[shell->len++] = '\t';
	}
	else
	{
		shell->cmds[shell->len++] = '\t';
		shell->cmds[shell->len++] = shell->input[shell->i];
		shell->cmds[shell->len++] = '\t';
	}
}

void	ft_args_copy(t_parsing *shell)
{
	if (!shell->input || !shell->input[0] || shell->bol == -1)
		ft_free_args(shell);
	shell->i = 0;
	shell->len = 0;
	while (shell->input && shell->input[shell->i])
	{
		if (shell->input[shell->i] == 34 || shell->input[shell->i] == 39)
			ft_str_copy(shell);
		else if (ft_check_double_operators(shell))
		{
			shell->cmds[shell->len++] = '\t';
			shell->cmds[shell->len++] = shell->input[shell->i];
			shell->cmds[shell->len++] = shell->input[++shell->i];
			shell->cmds[shell->len++] = '\t';
		}
		else if (ft_check_single_operators(shell))
			ft_this_condition_function(shell);
		else if (shell->input[shell->i] == ' '
			|| shell->input[shell->i] == '\t')
			shell->cmds[shell->len++] = '\t';
		else
			shell->cmds[shell->len++] = shell->input[shell->i];
		if (shell->input[shell->i])
			shell->i++;
	}
}

void	ft_delete_commits(t_parsing *shell)
{
	shell->i = 0;
	while (shell->temp[shell->i])
	{
		if (!ft_strcmp(shell->temp[shell->i], "#"))
		{
			while (shell->temp[shell->i])
			{
				//free(shell->temp[shell->i]);
				shell->temp[shell->i] = NULL;
				shell->i++;
			}
			return ;
		}
		shell->i++;
	}
}


void	ft_split_args(t_parsing *shell)
{
	ft_count_len_args(shell);
	if (shell->free == -1)
		return ;
	shell->cmds = ft_malloc(shell->len + 1);
	if (!shell->cmds)
		return ;
	ft_args_copy(shell);
	shell->cmds[shell->len] = '\0';
	shell->temp = ft_split(shell->cmds, '\t');
	if (!shell->temp)
		ft_free_args(shell);
	if (shell->free == -1)
		return ;
	ft_delete_commits(shell);
}
