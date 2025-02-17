
#include "../minishell.h"

void	ft_init_parsing(t_parsing *shell)
{
	shell->i = 0;
	shell->j = 0;
	shell->len = 0;
	shell->bol = 0;
	shell->free = 0;
	shell->brackets = 0;
	shell->cmds = NULL;
	shell->temp = NULL;
	shell->tree = NULL;
	shell->tokens = NULL;
	shell->lst_help1 = NULL;
	shell->lst_help2 = NULL;
}

int	ft_count_nodes_list(t_list *list)
{
	int	count;

	count = 0;
	while (list)
	{
		count++;
		list = list->next;
	}
	return (count);
}

int	ft_count_brackets(t_list *list)
{
	int	count;

	count = 0;
	while (list)
	{
		if (list->value && (!ft_strcmp(list->value[0], "(")
				|| !ft_strcmp(list->value[0], ")")))
			count++;
		list = list->next;
	}
	return (count);
}

void	ft_parsing(t_parsing *shell)
{
	ft_init_parsing(shell);
	if (ft_check_input_is_valid(shell))
	{
		// ft_here_doc(shell, shell->input);
		ft_split_args(shell);
		ft_check_syntax_errors(shell);
		shell->tree = ft_creat_ast_tree(shell);
		if (!shell->tree)
			return ;
		if ((ft_count_tree_nodes(shell->tree)
				!= (ft_count_nodes_list(shell->tokens)
					- ft_count_brackets(shell->tokens)))
			|| ft_ast_contains_brackets(shell->tree))
			ft_free_parsing(shell);
		if (shell->free != -1 && shell->tree)	//	temp
		{
			printf("\n----------Parsing----------\n\n");
			print_ast(shell->tree, 0, "root");  //	temp
			printf("\n\n\n----------exacution----------\n\n");
		}
	}
}

// *************** test parsing **********

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
