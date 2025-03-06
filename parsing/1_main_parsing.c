#include "../minishell.h"

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
		if (tmp && tmp->next && tmp->next->value && tmp->value
			&& !tmp->value[1] && ft_check_is_redirections(tmp->value[0])
			&& ft_check_is_operators(tmp->next->value[0]))
		{
			ft_free_parsing(shell);
			return ;
		}
		tmp = tmp->next;
	}
}


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
		return;
	shell->i = 0;
	shell->j = 0;
	while (shell->input[shell->i])
	{
		if (shell->input[shell->i] == 34 || shell->input[shell->i] == 39)
		{
			shell->chr = shell->input[shell->i++];
			while (shell->input[shell->i] && shell->input[shell->i] != shell->chr)
				shell->i++;
		}
		if (shell->input[shell->i] == '\n')
			shell->input[shell->i] = ' ';
		if (shell->input[shell->i])
			shell->i++;
	}
	ft_init_parsing(shell);
}

void	ft_init_tab(int *tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		tab[i] = 0;
		i++;
	}
}

int	ft_get_token_length(char *value)
{
	int	i;

	i = 0;
	while (value[i])
		i++;
	return (i);
}

void	ft_count_len_list(t_parsing *shell)
{
	ft_init_tab(shell->tab, 999);
	shell->j = 0;
	shell->lst_help1 = shell->tokens;
	while (shell->lst_help1)
	{
		shell->tab[shell->j] = ft_get_token_length(shell->lst_help1->value[0]);
		if (ft_check_is_redirections(shell->lst_help1->value[0]))
		{
			shell->lst_help1 = shell->lst_help1->next;
			shell->j++;
			while (shell->lst_help1 && !ft_check_is_operators(shell->lst_help1->value[0]))
			{
				shell->tab[shell->j] += ft_get_token_length(shell->lst_help1->value[0]);
				shell->lst_help1 = shell->lst_help1->next;
			}
			shell->j++;
		}
		else
		{
			shell->lst_help1 = shell->lst_help1->next;
			shell->j++;
		}
	}
	shell->len = shell->j;
}


/*
// void	ft_count_len_list(t_parsing *shell)
// {
// 	shell->j = 0;
// 	shell->i = -1;
// 	while (++shell->i < 999)
// 		shell->tab[shell->i] = 0;
// 	shell->lst_help1 = shell->tokens;
// 	while (shell->lst_help1)
// 	{
// 		shell->i = -1;
// 		while (shell->lst_help1->value[++shell->i])
// 			;
// 		shell->tab[shell->j] = shell->i;
// 		if (shell->lst_help1 && ft_check_is_redirections(shell->lst_help1->value[0]))
// 		{
// 			shell->lst_help1 = shell->lst_help1->next;
// 			shell->j++;
// 			while(shell->lst_help1)
// 			{
// 				if (ft_check_is_operators(shell->lst_help1->value[0]))
// 					break;
// 				shell->i = -1;
// 				while (shell->lst_help1->value[++shell->i])
// 					;
// 				shell->tab[shell->j] += shell->i;
// 				if (shell->lst_help1)
// 					shell->lst_help1 = shell->lst_help1->next;
// 			}
// 			shell->j++;
// 		}
// 		else if (shell->lst_help1)
// 		{
// 			shell->lst_help1 = shell->lst_help1->next;
// 			shell->j++;
// 		}
// 	}
// 	shell->len = shell->j;
// }
*/

void	ft_init_tmp(char **tmp, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		tmp[i] = NULL;
		i++;
	}
}

void	ft_fill_tmp(char **tmp, char **value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		tmp[i] = ft_strdup(value[i]);
		i++;
	}
	tmp[i] = NULL;
}

void	ft_store_redirection(t_parsing *shell, char **tmp, int *j, t_list **head)
{
	int		k;
	t_list	*new;

	k = 0;
	shell->tokens = shell->tokens->next;
	while (shell->tokens && !ft_check_is_operators(shell->tokens->value[0]))
	{
		if (!k)
			tmp = ft_malloc((shell->tab[(*j)++] + 1) * sizeof(char *));
		ft_fill_tmp(tmp + k, shell->tokens->value);
		k += ft_get_token_length(shell->tokens->value[0]);
		shell->tokens = shell->tokens->next;
	}
	if (k)
	{
		tmp[k] = NULL;
		new = ft_lstnew(tmp);
		ft_lstadd_back(head, new);
	}
}

void	ft_move_redirections(t_parsing *shell)
{
	int		j;
	char	**tmp;
	t_list	*head;
	t_list	*new;

	j = 0;
	head = NULL;
	tmp = NULL;
	ft_count_len_list(shell);
	shell->lst_help1 = shell->tokens;
	while (shell->tokens)
	{
		tmp = ft_malloc((shell->tab[j++] + 1) * sizeof(char *));
		ft_fill_tmp(tmp, shell->tokens->value);
		if (ft_check_is_redirections(shell->tokens->value[0]))
			ft_store_redirection(shell, tmp, &j, &head);
		else
			shell->tokens = shell->tokens->next;
		new = ft_lstnew(tmp);
		ft_lstadd_back(&head, new);
	}
	shell->tokens = head;
}


/*
// void	ft_move_redirections(t_parsing *shell)
// {
// 	int	i = 0;
// 	int	j = 0;
// 	int	k = 0;
// 	char	**tmp = NULL;
// 	t_list *head = NULL, *new = NULL;
// 	ft_count_len_list(shell);
// 	shell->lst_help1 = shell->tokens;
// 	while (shell->tokens)
// 	{
// 		if (tmp)
// 			tmp = NULL;
// 		tmp = ft_malloc((shell->tab[j++] + 1) * sizeof(char *));
// 		i = 0;
// 		while (shell->tokens->value[i])
// 		{
// 			tmp[i] = ft_strdup(shell->tokens->value[i]);
// 			i++;
// 		}
// 		if (i != -1)
// 			tmp[i] = NULL;
// 		if (shell->tokens && ft_check_is_redirections(shell->tokens->value[0]))
// 		{
// 			if (tmp[0])
// 			{
// 				tmp[i] = NULL;
// 				new = ft_lstnew(tmp);
// 				ft_lstadd_back(&head, new);
// 				if (tmp)
// 					tmp = NULL;
// 			}
// 			shell->tokens = shell->tokens->next;
// 			k = 0;
// 			while(shell->tokens)
// 			{
// 				if (ft_check_is_operators(shell->tokens->value[0]))
// 					break;
// 				i = 0;
// 				while (shell->tokens->value[i])
// 				{
// 					if (!k)
// 					{
// 						if (tmp)
// 							tmp = NULL;
// 						tmp = ft_malloc((shell->tab[j++] + 1) * sizeof(char *));
// 					}
// 					tmp[k] = ft_strdup(shell->tokens->value[i]);
// 					k++;
// 					i++;
// 				}
// 				if (shell->tokens)
// 					shell->tokens = shell->tokens->next;
// 			}
// 			if (k)
// 				tmp[k] = NULL;
// 		}
// 		else if (shell->tokens)
// 			shell->tokens = shell->tokens->next;
		
// 		new = ft_lstnew(tmp);
// 		ft_lstadd_back(&head, new);
// 	}
// 	if (tmp)
// 		tmp = NULL;
// 	shell->tokens = NULL;
// 	shell->lst_help1 = NULL;
// 	shell->lst_help2 = NULL;
// 	shell->tokens = head;
// }
*/

int	ft_count_heredoc(t_parsing *shell)
{
	if (!shell || !shell->tokens)
	{
		ft_free_parsing(shell);
		return (0);
	}
	shell->len = 0;
	shell->lst_help1 = shell->tokens;
	while (shell->lst_help1)
	{
		if (shell->lst_help1->value && shell->lst_help1->value[0]
			&& !shell->lst_help1->value[1]
			&& !ft_strcmp(shell->lst_help1->value[0], "<<"))
			shell->len++;
		shell->lst_help1 = shell->lst_help1->next;
	}
	if (shell->len >= 17)
	{
		ft_free_parsing(shell);
		return (0);
	}
	return (1);
}

int	ft_process_input(t_parsing *shell, int bol, t_exaction *data)
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
		return (0);
	if ((ft_count_tree_nodes(shell->tree)
			!= (ft_count_nodes_list(shell->tokens)
				- ft_count_brackets(shell->tokens)))
		|| ft_ast_contains_brackets(shell->tree))
	{
		ft_free_parsing(shell);
		return (0);
	}
	return (1);
}

void	ft_parsing(t_parsing *shell, int bol, t_exaction *data)
{
	if (!shell || !shell->input || !shell->input[0])
		return ;
	ft_init_parsing(shell);
	if (!ft_check_input_is_valid(shell))
		return;
	if (!ft_process_input(shell, bol, data))
		return;
	if (shell->free == -1 || !ft_count_heredoc(shell))
		return;
	ft_check_other_errors(shell);
	if (shell->free == -1)
		return;
	if (!bol)
	{
		ft_pars_redirections(shell, shell->tokens);
		ft_parsing(shell, 1337, data);
	}
}


/*
// void	ft_parsing(t_parsing *shell, int bol, t_exaction *data)
// {
// 	ft_init_parsing(shell);
// 	if (ft_check_input_is_valid(shell))
// 	{
// 		if (bol)
// 		{
// 			ft_replace_newline_with_space(shell);
// 			ft_replace_tabs_with_spaces(shell, shell->input);
// 			ft_here_doc(shell, shell->input, data);
// 		}
// 		ft_split_args(shell);
// 		ft_check_syntax_errors(shell);
// 		if (bol)
// 			ft_move_redirections(shell);
// 		shell->tree = ft_creat_ast_tree(shell);
// 		if (!shell->tree)
// 			return ;
// 		if ((ft_count_tree_nodes(shell->tree)
// 				!= (ft_count_nodes_list(shell->tokens)
// 					- ft_count_brackets(shell->tokens)))
// 			|| ft_ast_contains_brackets(shell->tree))
// 			ft_free_parsing(shell);
	
// 		if (shell->free == -1 || !ft_count_heredoc(shell))
// 			return;
// 		ft_check_other_errors(shell);
// 		if (shell->free == -1)
// 			return;
// 		if (!bol)
// 		{
// 			ft_pars_redirections(shell, shell->tokens);
// 			ft_parsing(shell, 1337, data);
// 			return ;
// 		}
// 	}
// }
*/


/*
// if (shell->free != -1 && shell->tree)	//	temp
// {
// 	printf("\n----------Parsing----------\n\n");
// 	print_ast(shell->tree, 0, "root");  //	temp
// 	printf("\n\n\n----------exacution----------\n\n");
// }
// *************** data parsing **********

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
*/