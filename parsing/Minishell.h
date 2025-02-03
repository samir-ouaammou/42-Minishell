#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	char			**value;
	struct s_list	*next;
}					t_list;

typedef struct s_ast
{
	char			**value;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

typedef struct s_parsing
{
	int				i;
	int				j;
	int				bol;
	int				len;
	int				free;
	int				parent;
	int				brackets;
	int				priority;
	char			chr;
	char			*cmds;
	char			*input;
	char			**temp;
	t_ast			*three;
	t_list			*tokens;
	t_list			*lst_help1;
	t_list			*lst_help2;
	t_list			*start_node;
	t_list			*end_node;
}					t_parsing;

void				ft_free_ast(t_ast *node);
void				ft_parsing(t_parsing *shell);
void				ft_free_args(t_parsing *shell);
void				ft_split_args(t_parsing *shell);
void				ft_free_tokens(t_parsing *shell);
void				ft_skip_string(t_parsing *shell);
void				ft_free_parsing(t_parsing *shell);
void				ft_count_len_args(t_parsing *shell);
int					ft_get_symbol_type(t_parsing *shell);
t_ast				*ft_creat_ast_three(t_parsing *shell);
void				ft_check_syntax_errors(t_parsing *shell);
int					ft_check_single_operators(t_parsing *shell);
int					ft_check_double_operators(t_parsing *shell);
void				ft_check_operator_position(t_parsing *shell);
t_list				*ft_get_list_node(t_list *tokens, int index);
int					ft_is_redirections(t_parsing *shell, int index);
t_ast				*ft_creat_ast_node(t_parsing *shell, char **value);
int					ft_is_logical_operators(t_parsing *shell, int index);
t_ast				*ft_build_command_tree(t_parsing *shell, int start,
						int end);
t_ast				*ft_create_and_build_ast_node(t_parsing *shell, int start,
						int i, int end);

void				print_ast(t_ast *node, int level, char *branch);

#endif
