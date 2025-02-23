#include "../minishell.h"


void	ft_init_parsing(t_parsing *shell)
{
	shell->i = 0;
	shell->j = 0;
	shell->bol = 0;
	shell->len = 0;
	shell->end = 0;
	shell->fd = -1;
	shell->free = 0;
	shell->start = 0;
	shell->parent = 0;
	shell->brackets = 0;
	shell->priority = 0;
	shell->cmds = NULL;
	shell->name = NULL;
	shell->itoa = NULL;
	shell->stop = NULL;
	shell->line = NULL;
	shell->help = NULL;
	shell->temp = NULL;
	shell->tree = NULL;
	shell->tokens = NULL;
	shell->lst_help1 = NULL;
	shell->lst_help2 = NULL;
	shell->start_node = NULL;
	shell->end_node = NULL;
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

void	ft_check_other_errors(t_parsing *shell)
{
	if (!shell || !shell->tokens)
	{
		ft_free_parsing(shell);
		return ;
	}
	t_list *tmp;
	
	tmp = shell->tokens;

	while (tmp)
	{
		if (tmp && tmp->next && tmp->next->value && tmp->value && !tmp->value[1] && ft_check_is_redirections(tmp->value[0]) && ft_check_is_operators(tmp->next->value[0]))
		{
			ft_free_parsing(shell);
			return ;
		}
		tmp = tmp->next;
	}
}

void	ft_parsing(t_parsing *shell, int bol)
{
	ft_init_parsing(shell);
	if (ft_check_input_is_valid(shell))
	{
		if (!bol)
			ft_here_doc(shell, shell->input);
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
		if (shell->free == -1)
			return;
		ft_check_other_errors(shell);
		if (shell->free == -1)
			return;
		if (!bol)
		{
			ft_pars_redirections(shell, shell->tokens);
			ft_parsing(shell, 1337);
			return ;			//  tmp
		}
	}
	// else ////-------------------
	// {
		// if (shell->free != -1 && shell->tree)	//	temp
		// {
		// 	printf("\n----------Parsing----------\n\n");
		// 	print_ast(shell->tree, 0, "root");  //	temp
		// 	printf("\n\n\n----------exacution----------\n\n");
		// }
	// }   //-------------------
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
