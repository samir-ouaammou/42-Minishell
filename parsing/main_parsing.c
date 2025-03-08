/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaammo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 01:03:54 by souaammo          #+#    #+#             */
/*   Updated: 2025/03/08 01:03:55 by souaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_move_redirections(t_parsing *shell)
{
	int		i;
	int		j;
	int		k;
	t_list	*head;
	t_list	*new;

	head = NULL;
	ft_init_move_vars(shell, &i, &j, &k);
	while (shell->tokens)
	{
		ft_create_temp_array(shell, &i, &j);
		if (shell->tokens && ft_check_is_redirections(shell->tokens->value[0]))
			ft_handle_redirections(shell, &head, &j, &k);
		else if (shell->tokens)
			shell->tokens = shell->tokens->next;
		new = ft_lstnew(shell->tmp);
		ft_lstadd_back(&head, new);
	}
	ft_cleanup_tokens(shell, head);
}

int	ft_check_is_operators(char *str)
{
	if (!str || !str[0])
		return (0);
	return (!ft_strcmp(str, "|") || !ft_strcmp(str, "||") || !ft_strcmp(str,
			"&&") || !ft_strcmp(str, "(") || !ft_strcmp(str, ")"));
}

int	ft_check_is_redirections(char *str)
{
	if (!str || !str[0])
		return (0);
	return (!ft_strcmp(str, "<") || !ft_strcmp(str, ">") || !ft_strcmp(str,
			"<<") || !ft_strcmp(str, ">>"));
}

void	ft_parsing_preprocessing(t_parsing *shell, int bol, t_exaction *data)
{
	ft_init_parsing(shell);
	if (!ft_check_input_is_valid(shell))
		return ;
	if (bol)
	{
		ft_replace_newline_with_space(shell);
		ft_replace_tabs_with_spaces(shell, shell->input);
		ft_here_doc(shell, data, shell->input, 0);
	}
	ft_split_args(shell);
	ft_check_syntax_errors(shell);
	if (bol)
		ft_move_redirections(shell);
}

void	ft_parsing(t_parsing *shell, int bol, t_exaction *data)
{
	ft_parsing_preprocessing(shell, bol, data);
	shell->tree = ft_creat_ast_tree(shell);
	if (!shell->tree)
		return ;
	if ((ft_count_tree_nodes(shell->tree) != (ft_count_nodes_list(shell->tokens)
				- ft_count_brackets(shell->tokens)))
		|| ft_ast_contains_brackets(shell->tree))
		ft_free_parsing(shell);
	if (shell->free == -1 || !ft_count_heredoc(shell))
		return ;
	ft_check_other_errors(shell);
	if (shell->free == -1)
		return ;
	if (!bol)
	{
		ft_pars_redirections(shell, shell->tokens);
		ft_parsing(shell, 1337, data);
		return ;
	}
	// if (shell->free != -1 && shell->tree)	//	temp
	// 	{
	// 		printf("\n----------Parsing----------\n\n");
	// 		print_ast(shell->tree, 0, "root");  //	temp
	// 		printf("\n\n\n----------exacution----------\n\n");
		// }
}


// // *************** data parsing **********
// 		if (shell->free != -1 && shell->tree)	//	temp
// 		{
// 			printf("\n----------Parsing----------\n\n");
// 			print_ast(shell->tree, 0, "root");  //	temp
// 			printf("\n\n\n----------exacution----------\n\n");
// 		}

void	print_ast(t_ast *node, int level, char *branch)
{
	int	i;
	int	j;

	if (!node)
		return ;

	i = 0;
	while (i < level)
	{
		printf("   ");
		i++;
	}
	printf("[%s]   ", branch);
	if (node->value)
	{
		j = 0;
		while (node->value[j])
		{
			printf("{%s} ", node->value[j]);
			j++;
		}
	}
	printf("\n");
	print_ast(node->left, level + 1, "left");
	print_ast(node->right, level + 1, "right");
}

