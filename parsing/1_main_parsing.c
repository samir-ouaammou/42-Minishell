
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
	shell->three = NULL;
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
		ft_split_args(shell);
		ft_check_syntax_errors(shell);
		shell->three = ft_creat_ast_three(shell);
		if (!shell->three)
			return ;
		if ((ft_count_tree_nodes(shell->three)
				!= (ft_count_nodes_list(shell->tokens)
					- ft_count_brackets(shell->tokens)))
			|| ft_ast_contains_brackets(shell->three))
			ft_free_parsing(shell);
		// if (shell->free != -1 && shell->three)	//	temp
		// {
		// 	printf("\n----------Parsing----------\n\n");
		// 	print_ast(shell->three, 0, "root");  //	temp
		// 	printf("\n\n\n----------exacution----------\n\n");
		// }
	}
}

char	*ft_check_quots(char *str, int *quots, int *newline, t_data *data)
{
	//int		i;
	int		len;
	char	*res;
	char	*tmp;

	*newline = 0;
	*quots = 2;
	res = NULL;
	tmp = NULL;
	len = ft_strlen(str);
	if (str && str[0] && str[len - 1] && str[0] == 39 && str[len - 1] == 39)//               "1" "1"
	{
		*quots = 1;
		tmp = ft_strstr(data->input, str);

		if (tmp && tmp[0] && tmp[len] && (tmp[len] == ' ' || tmp[len] == '\t' || tmp[len] == '\n'))
			*newline = 1;
		res = ft_strtrim(str, "'");
	}
	else if (str && str[0] && str[len - 1] && str[0] == 34 && str[len - 1] == 34)
	{
		tmp = ft_strstr(data->input, str);
		if (tmp && tmp[0] && tmp[len] && (tmp[len] == ' ' || tmp[len] == '\t' || tmp[len] == '\n'))
			*newline = 1;
		res = ft_strtrim(str, "\"");
	}
	else
	{
		res = ft_strdup(str);
		*newline = 1;
	}
	// free(data->input);
	// printf("len ->%d\n\ninput ->%s\n\n", len, data->input);
	// if (tmp[len - 1])
		// data->input = &tmp[len - 1];
	// else
	// 	data->input = &tmp[len];
	return (res);
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
			printf("%s ", node->value[j]);
			j++;
		}
	}
	printf("\n");
	print_ast(node->left, level + 1, "left");
	print_ast(node->right, level + 1, "right");
}
