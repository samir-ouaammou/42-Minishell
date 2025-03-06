#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <dirent.h>
# include <stdlib.h>
# include <string.h>
# include <fnmatch.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include "malloc/malloc.h"
# include "./libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>

extern int g_v;
extern int g_v_child;

# define SUCCESS 0
# define FAILED 1

typedef struct s_ast
{
	char				**value;
	struct s_ast		*left;
	struct s_ast		*right;
}						t_ast;

typedef struct s_data	t_exaction_struct;

// struct Pxaction
typedef struct s_parsing
{
	int					i;
	int					j;
	int					bol;
	int					len;
	int					free;
	int					start;
	int					end;
	int					fd;
	int					nbr;
	int					tab[1000];
	int					parent;
	int					brackets;
	int					priority;
	char				chr;
	char				*cmds;
	char				*input;
	char				*name;
	char				*itoa;
	char				**stop;
	char				*line;
	char				*history;
	char				*help;
	char				**temp;
	t_ast				*tree;
	t_list				*tokens;
	t_list				*lst_help1;
	t_list				*lst_help2;
	t_list				*start_node;
	t_list				*end_node;
	t_exaction_struct	*data;
}						t_parsing;

// struct Exaction
typedef struct s_exaction
{
	char				**matches;
	char				**DollarSign;
	char				**env;
	char				**env_buffer;
	char				**export;
	char				**export_buffer;
	int					status;
	int					exit_status;
	int					check_operator;
	int					check_parenthese;
	int					check_pipe;
	int					check_exe;
	int					check_fmatch;
	int					save_index;
	int					stdout_backup;
	int					stdin_backup;
	char				*name_pro;
	char				*input;
	int					fd_file;
	int					fd_file2;
	int					count_ok;
	int					is_plus;
	char				*save_pwd;
	int flag;
	int pid_child;
	int bol;
	int lll;
	int					is_foreground;
	t_parsing			*shell;
}						t_exaction;

// Functions Pxaction

void					ft_free_args(t_parsing *shell);
void					ft_split_args(t_parsing *shell);
int						ft_count_tree_nodes(t_ast *tree);
int						ft_check_is_operators(char *str);
void					ft_skip_string(t_parsing *shell);
void					ft_init_parsing(t_parsing *shell);
void					ft_free_parsing(t_parsing *shell);
int						ft_check_is_redirections(char *str);
void					ft_count_len_args(t_parsing *shell);
int						ft_get_symbol_type(t_parsing *shell);
t_ast					*ft_creat_ast_tree(t_parsing *shell);
int						ft_ast_contains_brackets(t_ast *tree);
void					ft_check_syntax_errors(t_parsing *shell);
int						ft_check_input_is_valid(t_parsing *shell);
int						ft_check_single_operators(t_parsing *shell);
int						ft_check_double_operators(t_parsing *shell);
void					ft_check_operator_position(t_parsing *shell);
t_list					*ft_get_list_node(t_list *tokens, int index);
int						ft_is_redirections(t_parsing *shell, int index);
t_ast					*ft_creat_ast_node(t_parsing *shell, char **value);
int						ft_is_logical_operators(t_parsing *shell, int index);
void					ft_pars_redirections(t_parsing *shell, t_list *list);
void					ft_parsing(t_parsing *shell, int bol, t_exaction *data);
void					ft_remove_quots(char **str, t_exaction *data, short bol);
void					ft_here_doc(t_parsing *shell, char *str, t_exaction *data);
t_ast					*ft_build_command_tree(t_parsing *shell, int start, int end);
int						is_wildcard_match(const char *wildcard, const char *filename);
t_ast					*ft_create_and_build_ast_node(t_parsing *shell, int start, int i, int end);
void	print_ast(t_ast *node, int level, char *branch); //////////////////////////////////temp

// Functions Exaction

void					free_all(char **args);
int						is_operator(char *str);
char					*get_str_Dollars(char *str);
char					*add_double_quotes(char *str);
int						builtin_pwd(t_exaction *data);
int						check_special_chars(char **args);
void					copy_string(char *str, char *res);
int						count_args(char **args, int start);
int						is_builtin(char *cmd, t_exaction *data);
void					exaction(t_ast *root, t_exaction *data);
void					read_env(t_exaction *data, char **envp);
void					read_env(t_exaction *data, char **envp);
int						builtin_cd(char **args, t_exaction *data);
char					*get_path_env(char *cmd, t_exaction *data);
int						builtin_env(char **args, t_exaction *data);
int						builtin_echo(char **str, t_exaction *data);
char					*find_str_env(char *str, t_exaction *data);
int						execute_ast(t_ast *root, t_exaction *data);
int						execute_pipe(t_ast *node, t_exaction *data);
int						builtin_exit(char **args, t_exaction *data);
int						builtin_unset(char **args, t_exaction *data);
int						execute_command(char **cmd, t_exaction *data);
char					*process_strings(char *str, t_exaction *data);
int						builtin_export(char **args, t_exaction *data);
size_t					calculate_length(char *str, t_exaction *data);
int						open_input_file(t_ast *node, t_exaction *data);
char					**copy_args(char **args, int start, int count);
int						execute_heredoc(t_ast *node, t_exaction *data);
int						handle_wildcards(char **args, t_exaction *data);
int						execute_redir_inp(t_ast *node, t_exaction *data);
int						execute_redirection(t_ast *root, t_exaction *data);
char					*add_double_quotes_plus(char *str_export, char *str);
size_t					handle_exit_status_length(t_exaction *data, int *index);
void					process_variable(char *str, char *res, t_exaction *data);
int						check_and_open_file(t_ast *node, t_exaction *data, char *type);
size_t					handle_env_var_length(char *str, t_exaction *data, int *index);
char					**merge_command_args(t_ast *node, int count_left, int count_right);
void					handle_env_var(char *str, char *res, t_exaction *data, int *res_index); // char *process_strings(char *str, t_exaction *data);
int						execute_redir_RightArrow_redirout(t_ast *node, t_exaction *data, char *type);
struct s_exaction *test();
void *ft_alloc(size_t size, char c);
void handle_sigint(int sig);
void *ft_malloc(size_t size);
void *ft_alloc(size_t size, char c);
#endif
