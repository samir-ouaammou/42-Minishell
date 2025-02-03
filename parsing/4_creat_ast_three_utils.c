#include "../libft/libft.h"
#include "Minishell.h"

t_ast	*ft_creat_ast_node(t_parsing *shell, char **value)
{
	t_ast	*new_node;

	if (!value || !value[0])
		return (ft_free_args(shell), NULL);
	new_node = malloc(sizeof(t_ast));
	if (!new_node)
		return (ft_free_args(shell), NULL);
	shell->len = 0;
	while (value && value[shell->len])
		shell->len++;
	new_node->value = malloc((shell->len + 1) * sizeof(char *));
	if (!new_node->value)
		return (free(new_node), new_node = NULL, ft_free_args(shell), NULL);
	shell->len = 0;
	while (value && value[shell->len])
	{
		new_node->value[shell->len] = ft_strdup(value[shell->len]);
		shell->len++;
	}
	new_node->value[shell->len] = NULL;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

t_list	*ft_get_list_node(t_list *tokens, int index)
{
	int	i;

	i = 0;
	while (tokens && i < index)
	{
		tokens = tokens->next;
		i++;
	}
	return (tokens);
}

int	ft_get_symbol_type(t_parsing *shell)
{
	if (!shell | !shell->lst_help2 || !shell->lst_help2->value)
		return (-1);
	if (!ft_strcmp(shell->lst_help2->value[0], "||")
		|| !ft_strcmp(shell->lst_help2->value[0], "&&"))
		return (0);
	if (!ft_strcmp(shell->lst_help2->value[0], "|"))
		return (1);
	if (!ft_strcmp(shell->lst_help2->value[0], "<")
		|| !ft_strcmp(shell->lst_help2->value[0], ">")
		|| !ft_strcmp(shell->lst_help2->value[0], "<<")
		|| !ft_strcmp(shell->lst_help2->value[0], ">>"))
		return (2);
	return (-1);
}

t_ast	*ft_create_and_build_ast_node(t_parsing *shell, int start, int i,
		int end)
{
	t_ast	*node;

	node = ft_creat_ast_node(shell, shell->lst_help2->value);
	if (shell->free == -1)
		return (NULL);
	node->left = ft_build_command_tree(shell, start, i - 1);
	node->right = ft_build_command_tree(shell, i + 1, end);
	return (node);
}
