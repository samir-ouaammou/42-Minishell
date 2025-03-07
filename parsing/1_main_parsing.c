#include "../minishell.h"

void ft_initialize_tab(t_parsing *shell)
{
    shell->j = 0;
    shell->i = -1;
    while (++shell->i < 999)
        shell->tab[shell->i] = 0;
    shell->lst_help1 = shell->tokens;
}

void ft_process_redirections(t_parsing *shell)
{
    shell->lst_help1 = shell->lst_help1->next;
    shell->j++;
    while (shell->lst_help1)
    {
        if (ft_check_is_operators(shell->lst_help1->value[0]))
            break;
        shell->i = -1;
        while (shell->lst_help1->value[++shell->i])
            ;
        shell->tab[shell->j] += shell->i;
        shell->lst_help1 = shell->lst_help1->next;
    }
    shell->j++;
}

void ft_count_len_list(t_parsing *shell)
{
    ft_initialize_tab(shell);
    while (shell->lst_help1)
    {
        shell->i = -1;
        while (shell->lst_help1->value[++shell->i])
            ;
        shell->tab[shell->j] = shell->i;
        if (ft_check_is_redirections(shell->lst_help1->value[0]))
            ft_process_redirections(shell);
        else
        {
            shell->lst_help1 = shell->lst_help1->next;
            shell->j++;
        }
    }
    shell->len = shell->j;
}


/*
void	ft_count_len_list(t_parsing *shell)
{
	shell->j = 0;
	shell->i = -1;
	while (++shell->i < 999)
		shell->tab[shell->i] = 0;
	shell->lst_help1 = shell->tokens;
	while (shell->lst_help1)
	{
		shell->i = -1;
		while (shell->lst_help1->value[++shell->i])
			;
		shell->tab[shell->j] = shell->i;
		if (shell->lst_help1 && ft_check_is_redirections(shell->lst_help1->value[0]))
		{
			shell->lst_help1 = shell->lst_help1->next;
			shell->j++;
			while(shell->lst_help1)
			{
				if (ft_check_is_operators(shell->lst_help1->value[0]))
					break;
				shell->i = -1;
				while (shell->lst_help1->value[++shell->i])
					;
				shell->tab[shell->j] += shell->i;
				if (shell->lst_help1)
					shell->lst_help1 = shell->lst_help1->next;
			}
			shell->j++;
		}
		else if (shell->lst_help1)
		{
			shell->lst_help1 = shell->lst_help1->next;
			shell->j++;
		}
	}
	shell->len = shell->j;
}
*/

void	ft_move_redirections(t_parsing *shell)
{
	int	i = 0;
	int	j = 0;
	int	k = 0;
	char	**tmp = NULL;
	t_list *head = NULL, *new = NULL;
	ft_count_len_list(shell);
	shell->lst_help1 = shell->tokens;
	while (shell->tokens)
	{
		if (tmp)
			tmp = NULL;
		tmp = ft_malloc((shell->tab[j++] + 1) * sizeof(char *));
		i = 0;
		while (shell->tokens->value[i])
		{
			tmp[i] = ft_strdup(shell->tokens->value[i]);
			i++;
		}
		if (i != -1)
			tmp[i] = NULL;
		if (shell->tokens && ft_check_is_redirections(shell->tokens->value[0]))
		{
			if (tmp[0])
			{
				tmp[i] = NULL;
				new = ft_lstnew(tmp);
				ft_lstadd_back(&head, new);
				if (tmp)
					tmp = NULL;
			}
			shell->tokens = shell->tokens->next;
			k = 0;
			while(shell->tokens)
			{
				if (ft_check_is_operators(shell->tokens->value[0]))
					break;
				i = 0;
				while (shell->tokens->value[i])
				{
					if (!k)
					{
						if (tmp)
							tmp = NULL;
						tmp = ft_malloc((shell->tab[j++] + 1) * sizeof(char *));
					}
					tmp[k] = ft_strdup(shell->tokens->value[i]);
					k++;
					i++;
				}
				if (shell->tokens)
					shell->tokens = shell->tokens->next;
			}
			if (k)
				tmp[k] = NULL;
		}
		else if (shell->tokens)
			shell->tokens = shell->tokens->next;
		
		new = ft_lstnew(tmp);
		ft_lstadd_back(&head, new);
	}
	if (tmp)
		tmp = NULL;
	shell->tokens = NULL;
	shell->lst_help1 = NULL;
	shell->lst_help2 = NULL;
	shell->tokens = head;
}

void	ft_parsing(t_parsing *shell, int bol, t_exaction *data)
{
	ft_init_parsing(shell);
	if (ft_check_input_is_valid(shell))
	{
		if (bol)
		{
			ft_replace_newline_with_space(shell);
			ft_replace_tabs_with_spaces(shell, shell->input);
			ft_here_doc(shell, shell->input, data);
		}
		ft_split_args(shell);
		ft_check_syntax_errors(shell);
		if (bol)
			ft_move_redirections(shell);
		shell->tree = ft_creat_ast_tree(shell);
		if (!shell->tree)
			return ;
		if ((ft_count_tree_nodes(shell->tree)
				!= (ft_count_nodes_list(shell->tokens)
					- ft_count_brackets(shell->tokens)))
			|| ft_ast_contains_brackets(shell->tree))
			ft_free_parsing(shell);
	
		if (shell->free == -1 || !ft_count_heredoc(shell))
			return;
		ft_check_other_errors(shell);
		if (shell->free == -1)
			return;
		if (!bol)
		{
			ft_pars_redirections(shell, shell->tokens);
			ft_parsing(shell, 1337, data);
			return ;
		}
	}
}

/*
// *************** data parsing **********
		// if (shell->free != -1 && shell->tree)	//	temp
		// {
		// 	printf("\n----------Parsing----------\n\n");
		// 	print_ast(shell->tree, 0, "root");  //	temp
		// 	printf("\n\n\n----------exacution----------\n\n");
		// }

// void	print_ast(t_ast *node, int level, char *branch)
// {
// 	int	i;
// 	int	j;

// 	if (!node)
// 		return ;

// 	i = 0;
// 	while (i < level)
// 	{
// 		printf("   ");
// 		i++;
// 	}
// 	printf("[%s]   ", branch);
// 	if (node->value)
// 	{
// 		j = 0;
// 		while (node->value[j])
// 		{
// 			printf("{%s} ", node->value[j]);
// 			j++;
// 		}
// 	}
// 	printf("\n");
// 	print_ast(node->left, level + 1, "left");
// 	print_ast(node->right, level + 1, "right");
// }
*/