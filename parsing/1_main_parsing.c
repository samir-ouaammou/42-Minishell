#include "../libft/libft.h"
#include "Minishell.h"

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

int	ft_check_input_is_valid(t_parsing *shell)
{
	if (!shell || !shell->input)
		return (0);
	shell->i = 0;
	while (shell->input && shell->input[shell->i])
	{
		if (shell->input[shell->i] != ' ' && shell->input[shell->i] != '\t'
			&& shell->input[shell->i] != '\n')
			break ;
		shell->i++;
	}
	shell->len = ft_strlen(shell->input);
	if (shell->len != shell->i)
	{
		shell->i = 0;
		shell->len = 0;
		return (1);
	}
	return (0);
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
		if (ft_ast_contains_brackets(shell->three))
			ft_free_parsing(shell);
	}
	print_ast(shell->three, 0, "ROOT");  //	temp
}


// *************** main test **********

void	print_ast(t_ast *node, int level, char *branch)
{
	if (!node)
		return ;
	// طباعة المسافات حسب المستوى
	for (int i = 0; i < level; i++)
		printf("   ");
	// طباعة الفرع (LEFT / RIGHT) مع القيمة
	printf("[%s]   ", branch);
	if (node->value)
	{
		for (int j = 0; node->value[j]; j++)
			printf("%s ", node->value[j]);
	}
	printf("\n");
	// استدعاء للطباعة للفرع الأيسر
	print_ast(node->left, level + 1, "LEFT");
	// استدعاء للطباعة للفرع الأيمن
	print_ast(node->right, level + 1, "RIGHT");
}

int	main(int ac, char **av)
{
	t_parsing	shell;

	if (ac != 1)
	{
		write(2, "Error: Invalid number of arguments.\n", 36);
		exit(-1);
	}
	while (1)
	{
		shell.input = readline("➜ Minishell ");
		ft_parsing(&shell);
		if (shell.free == -1 && (!shell.tokens || !shell.three))
			write(2, "minishell: syntax error\n", 24);
		//	ft_ex();
		if (shell.input)
		{
			add_history(shell.input);
			ft_free_parsing(&shell);
		}
	}
	rl_clear_history();
	(void)av;
	return (0);
}
