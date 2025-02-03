#include "../libft/libft.h"
#include "Minishell.h"

int	ft_handle_brackets(t_parsing *shell, int start, int end)
{
	if (shell->start_node->value[0][0] == '('
		&& shell->end_node->value[0][0] == ')')
	{
		shell->brackets = 1;
		shell->lst_help1 = shell->start_node->next;
		shell->i = start + 1;
		while (shell->i < end)
		{
			if (!shell->lst_help1)
				break ;
			if (shell->lst_help1->value[0][0] == '(')
				shell->brackets++;
			else if (shell->lst_help1->value[0][0] == ')')
				shell->brackets--;
			if (shell->brackets == 0)
				break ;
			shell->lst_help1 = shell->lst_help1->next;
			shell->i++;
		}
		if (shell->brackets == 1)
			return (1);
	}
	return (0);
}

t_ast	*ft_find_priority_operator(t_parsing *shell, int start, int end)
{
	int	i;
	int	symbol_type;

	shell->lst_help2 = ft_get_list_node(shell->tokens, end);
	i = end;
	while (i >= start)
	{
		if (!shell->lst_help2)
			break ;
		if (shell->lst_help2->value[0][0] == ')')
			shell->parent++;
		else if (shell->lst_help2->value[0][0] == '(')
			shell->parent--;
		if (shell->parent == 0)
		{
			symbol_type = ft_get_symbol_type(shell);
			if ((shell->priority == 0 && symbol_type == 0)
				|| (shell->priority == 1 && symbol_type == 1)
				|| (shell->priority == 2 && symbol_type == 2))
				return (ft_create_and_build_ast_node(shell, start, i, end));
		}
		shell->lst_help2 = ft_get_list_node(shell->tokens, i - 1);
		i--;
	}
	return (NULL);
}

t_ast	*ft_build_command_tree(t_parsing *shell, int start, int end)
{
	t_ast	*node;

	if (start > end || !shell || shell->free == -1)
		return (NULL);
	shell->start_node = ft_get_list_node(shell->tokens, start);
	shell->end_node = ft_get_list_node(shell->tokens, end);
	if (!shell->start_node || !shell->start_node->value || !shell->end_node
		|| !shell->end_node->value)
		return (NULL);
	if (shell->start_node->value[0][0] == '('
		&& shell->end_node->value[0][0] == ')')
		if (ft_handle_brackets(shell, start, end))
			return (ft_build_command_tree(shell, start + 1, end - 1));
	shell->parent = 0;
	shell->priority = 0;
	while (shell->priority < 3)
	{
		shell->parent = 0;
		node = ft_find_priority_operator(shell, start, end);
		if (node)
			return (node);
		shell->priority++;
	}
	return (ft_creat_ast_node(shell, shell->start_node->value));
}

t_ast	*ft_creat_ast_three(t_parsing *shell)
{
	if (!shell || !shell->tokens || shell->free == -1)
		return (NULL);
	shell->len = 0;
	shell->lst_help1 = shell->tokens;
	while (shell->lst_help1)
	{
		shell->len++;
		shell->lst_help1 = shell->lst_help1->next;
	}
	return (ft_build_command_tree(shell, 0, shell->len - 1));
}
