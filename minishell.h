#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include "./libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fnmatch.h>
# include <dirent.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
#include <errno.h>
# include <stdio.h>

# define SUCCESS 0
# define FAILED 1

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
	int				start;
	int				end;
	int				fd;
	int				nbr;
	int				parent;
	int				brackets;
	int				priority;
	char			chr;
	char			*cmds;
	char			*input;
	char			*name;
	char			*itoa;
	char			**stop;
	char			*line;
	char			**temp;
	t_ast			*tree;
	t_list			*tokens;
	t_list			*lst_help1;
	t_list			*lst_help2;
	t_list			*start_node;
	t_list			*end_node;
}					t_parsing;

typedef struct s_data
{
	char			**matches;
	char			**DollarSign;
	char			**env;
	int				status;
	int				exit_status;
	int				check_operator;
	int				check_parenthese;
	int				check_pipe;
	int				check_exe;
	int				check_fmatch;
	int				save_index;
	int				stdout_backup;
	int				stdin_backup;
	char			*name_pro;
	char			*input;
}					t_data;


// p
void ft_here_doc(t_parsing *shell, char *str);

void				ft_free_ast(t_ast *node);
void				ft_remove_quots(char **str);
void				ft_parsing(t_parsing *shell);
void				ft_free_args(t_parsing *shell);
void				ft_split_args(t_parsing *shell);
void				ft_free_tokens(t_parsing *shell);
int					ft_count_tree_nodes(t_ast *tree);
void				ft_skip_string(t_parsing *shell);
void				ft_free_parsing(t_parsing *shell);
void				ft_count_len_args(t_parsing *shell);
int					ft_get_symbol_type(t_parsing *shell);
t_ast				*ft_creat_ast_tree(t_parsing *shell);
int					ft_ast_contains_brackets(t_ast *tree);
void				ft_check_syntax_errors(t_parsing *shell);
int					ft_check_input_is_valid(t_parsing *shell);
int					ft_check_single_operators(t_parsing *shell);
int					ft_check_double_operators(t_parsing *shell);
void				ft_check_operator_position(t_parsing *shell);
t_list				*ft_get_list_node(t_list *tokens, int index);
int					ft_is_redirections(t_parsing *shell, int index);
t_ast				*ft_creat_ast_node(t_parsing *shell, char **value);
int					ft_is_logical_operators(t_parsing *shell, int index);
t_ast				*ft_build_command_tree(t_parsing *shell, int start, int end);
int					is_wildcard_match(const char *wildcard, const char *filename);
// char				*ft_check_quots(char *str, int *quots, int *newline, t_data *data);
t_ast				*ft_create_and_build_ast_node(t_parsing *shell, int start, int i, int end);

void				print_ast(t_ast *node, int level, char *branch); //temp
// e


int					builtin_pwd(void);
int builtin_exit(t_ast *node, t_data *data);
void				read_env(t_data *data, char **envp);
int					builtin_cd(char **args, t_data *data);
int					builtin_env(char **args, t_data *data);
int					builtin_echo(char **str, t_data *data);
int					builtin_unset(t_ast *node, t_data *data);
int					builtin_export(t_ast *node, t_data *data);
void				exaction(t_ast *root, t_data *data);
char *find_str_env(char *str, t_data *data);

char	*get_path_env(char *cmd, t_data *data);

int	execute_command(char **cmd, t_data *data);

int	execute_pipe(t_ast *node, t_data *data);

int	handle_wildcards(char **args, t_data *data);

int				execute_ast(t_ast *root, t_data *data);

void	execute_redir_inp(t_ast *node, t_data *data);


void	execute_redir_RightArrow_redirout(t_ast *node, t_data *data, char *type);

void	read_env(t_data *data, char **envp);

char	*find_str_env(char *str, t_data *data);

void	process_strings(t_ast *root, t_data *data);


int	is_operator(char *str);
int	is_builtin(char *cmd);

#endif
