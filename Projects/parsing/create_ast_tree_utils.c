/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast_tree_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaammo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 01:01:57 by souaammo          #+#    #+#             */
/*   Updated: 2025/03/08 01:01:59 by souaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_ast_contains_brackets(t_ast *node)
{
	int	i;

	if (!node || !node->value)
		return (0);
	i = 0;
	while (node->value[i])
	{
		if (node->value[i][0] == '(' || node->value[i][0] == ')')
			return (1);
		i++;
	}
	if (ft_ast_contains_brackets(node->left))
		return (1);
	if (ft_ast_contains_brackets(node->right))
		return (1);
	return (0);
}

void	ft_create_temp_array(t_parsing *shell, int *i, int *j)
{
	if (shell->tmp)
		shell->tmp = NULL;
	shell->tmp = ft_malloc((shell->tab[(*j)++] + 1) * sizeof(char *));
	*i = 0;
	while (shell->tokens->value[*i])
	{
		shell->tmp[*i] = ft_strdup(shell->tokens->value[*i]);
		(*i)++;
	}
	if (*i != -1)
		shell->tmp[*i] = NULL;
}

t_ast	*ft_creat_ast_node(t_parsing *shell, char **value)
{
	t_ast	*new_node;

	if (!value || !value[0])
		return (ft_free_args(shell), NULL);
	new_node = ft_malloc(sizeof(t_ast));
	if (!new_node)
		return (ft_free_args(shell), NULL);
	shell->len = 0;
	while (value && value[shell->len])
		shell->len++;
	new_node->value = ft_malloc((shell->len + 1) * sizeof(char *));
	if (!new_node->value)
		return (new_node = NULL, ft_free_args(shell), NULL);
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

t_ast	*ft_create_and_build_ast_node(t_parsing *shell,
									int start, int i, int end)
{
	t_ast	*node;

	node = ft_creat_ast_node(shell, shell->lst_help2->value);
	if (shell->free == -1)
		return (NULL);
	node->left = ft_build_command_tree(shell, start, i - 1);
	node->right = ft_build_command_tree(shell, i + 1, end);
	return (node);
}
