/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaammo <souaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 19:29:22 by aahaded           #+#    #+#             */
/*   Updated: 2025/03/08 00:58:50 by souaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include "malloc/malloc.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <fnmatch.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define SUCCESS 0
# define FAILED 1

typedef struct s_ast
{
	char				**value;
	struct s_ast		*left;
	struct s_ast		*right;
}						t_ast;

typedef struct s_data	t_exaction_struct;

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
	char				**tmp;
	char				**temp;
	t_ast				*tree;
	t_list				*tokens;
	t_list				*lst_help1;
	t_list				*lst_help2;
	t_list				*start_node;
	t_list				*end_node;
	t_exaction_struct	*data;
}						t_parsing;

typedef struct s_exaction
{
	char				**matches;
	char				**env;
	char				**export;
	char				**copy;
	char				*save_oldpwd;
	int					status;
	int					exit_status;
	char				*name_pro;
	int					count_ok;
	int					is_plus;
	char				*save_pwd;
	int					bol;
	int					is_foreground;
	int					space;
	int					num_proess;
}						t_exaction;

int						ft_is_single_operator(char c);
void					ft_free_args(t_parsing *shell);
int						ft_is_symbol(t_parsing *shell);
char					**ft_allocate_result(char *str);
int						ft_count_brackets(t_list *list);
void					ft_split_args(t_parsing *shell);
void					ft_tokens_list(t_parsing *shell);
int						ft_check_is_operators(char *str);
int						ft_count_tree_nodes(t_ast *tree);
int						ft_check_is_operators(char *str);
void					ft_skip_string(t_parsing *shell);
void					ft_init_parsing(t_parsing *shell);
int						ft_count_nodes_list(t_list *list);
void					ft_free_parsing(t_parsing *shell);
void					ft_init_here_doc(t_parsing *shell);
int						ft_count_heredoc(t_parsing *shell);
void					ft_count_len_list(t_parsing *shell);
int						ft_check_is_redirections(char *str);
int						ft_check_is_redirections(char *str);
void					ft_count_len_args(t_parsing *shell);
int						ft_get_symbol_type(t_parsing *shell);
t_ast					*ft_creat_ast_tree(t_parsing *shell);
int						ft_ast_contains_brackets(t_ast *tree);
void					ft_check_other_errors(t_parsing *shell);
void					ft_check_syntax_errors(t_parsing *shell);
int						ft_check_input_is_valid(t_parsing *shell);
void					process_input(t_parsing *shell, char *str);
void					ft_move_input(t_parsing *shell, char *str);
void					ft_extract_word(char *str, int *i, char *c);
int						ft_check_single_operators(t_parsing *shell);
int						ft_check_double_operators(t_parsing *shell);
void					ft_check_operator_position(t_parsing *shell);
t_list					*ft_get_list_node(t_list *tokens, int index);
void					ft_handle_quotes(t_parsing *shell, char *str);
char					*ft_move_flags(t_parsing *shell, t_list *list);
char					*ft_strjoin_and_free(char *s1, const char *s2);
void					ft_update_position(t_parsing *shell, char *str);
void					ft_replace_newline_with_space(t_parsing *shell);
int						ft_is_redirections(t_parsing *shell, int index);
int						ft_check_delimiter(t_parsing *shell, char *str);
int						count_words(char *str, int count, int i, char c);
void					ft_finalize_here_doc(t_parsing *shell, char *str);
void					ft_cleanup_tokens(t_parsing *shell, t_list *head);
int						is_wildcard_match(char *wildcard, char *filename);
t_ast					*ft_creat_ast_node(t_parsing *shell, char **value);
void					ft_find_delimiter_end(t_parsing *shell, char *str);
int						ft_is_logical_operators(t_parsing *shell, int index);
void					ft_pars_redirections(t_parsing *shell, t_list *list);
int						ft_check_unclosed_quotes(t_parsing *shell, char *str);
char					**ft_split_quots(char *str, char **res, int i, int j);
void					ft_create_temp_array(t_parsing *shell, int *i, int *j);
void					ft_parsing(t_parsing *shell, int bol, t_exaction *data);
t_list					*ft_creat_new_node(t_parsing *shell, int start,
							int end);
void					ft_remove_quots(char **str, t_exaction *data,
							short bol);
void					ft_replace_tabs_with_spaces(t_parsing *shell,
							char *input);
void					ft_init_move_vars(t_parsing *shell, int *i, int *j,
							int *k);
void					ft_handle_redirect_content(t_parsing *shell, int *j,
							int *k);
t_ast					*ft_build_command_tree(t_parsing *shell, int start,
							int end);
void					ft_here_doc(t_parsing *shell, t_exaction *data,
							char *str, int dolar);
void					ft_handle_redirections(t_parsing *shell, t_list **head,
							int *j, int *k);
t_ast					*ft_create_and_build_ast_node(t_parsing *shell,
							int start, int i, int end);
int						ft_process_delimiter(t_parsing *shell, char *str,
							t_exaction *data, int *dolar);
void					ft_read_and_process_heredoc_input(t_parsing *shell,
							int dolar, t_exaction *data);
void					print_ast(t_ast *node, int level, char *branch);

int						handle_child_exit_status(int status);
int						handle_forked_process(t_parsing *shell, int dolar,
							t_exaction *data);

int						is_operator(char *str);
void					sigint_handler(int sig);
char					*get_str_dollars(char *str);
char					*add_double_quotes(char *str);
int						builtin_pwd(t_exaction *data);
int						check_special_chars(char **args);
void					copy_string(char *str, char *res);
int						is_builtin(char *cmd, t_exaction *data);
void					exaction(t_ast *root, t_exaction *data);
void					read_env(char **envp, t_exaction *data);
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
int						open_input_file(t_ast *node, t_exaction *data);
int						execute_heredoc(t_ast *node, t_exaction *data);
int						handle_wildcards(char **args, t_exaction *data);
int						execute_redirection(t_ast *root, t_exaction *data);
char					*add_double_quotes_plus(char *str_export, char *str);
int						handle_exit_status_length(int *index);
void					process_variable(char *str, char *res,
							t_exaction *data);
int						handle_env_var_length(char *str, t_exaction *data,
							int *index);
void					handle_env_var(char *str, char *res, t_exaction *data,
							int *res_index);
struct s_exaction		*data_struc(void);
void					handle_signal(int sig);
void					print_export(t_exaction *data);
int						check_plus(char *str);
int						is_valid_export_identifier(char *str);
void					handle_plus_operator(int index, char **args);
int						update_env_var(char **args, t_exaction *data, char *str,
							int i);
int						update_export_var(char **args, t_exaction *data,
							char *str, int i);
int						add_new_env_var(char **args, t_exaction *data,
							int index);
int						add_new_export_var(char **args, t_exaction *data,
							int index);
int						add_default_export(char *str, t_exaction *data,
							int len);
int						count_export_entries(t_exaction *data);
int						strlen_without_plus(char *arg);
char					*get_key_part(char *str, char delimiter);
void					update_export_with_quotes(t_exaction *data, char *arg,
							int j, char *str);
int						is_directory(char *cmd);
void					update_shlvl(t_exaction *data);
char					*add_double_quotes_test(char *str);
int						contains_slash(char *cmd);
void					handle_exec_failure(char *cmd, int check_);
void					handle_execve_error(char **cmd, t_exaction *data);
char					*find_str_env(char *str, t_exaction *data);
void					check_shlvl(t_exaction *data);
void					initialize_and_copy_env_to_export(t_exaction *data);
int						check_pwd_exists(char **envp);
void					duplicate_value_array(t_ast *root, t_exaction *data);
int						calculate_length(char *str, t_exaction *data);
int						calculate_length_(char *str);
void					remove_extra_spaces(char *env_var);
int						handle_file_redirection_utils(t_ast *root, int *fd_out);
int						handle_file_redirection(t_ast *root,
							int *fd_in, int *fd_out);
int						is_assignment_format(char *str);
int						strlen_without_quotes(char *str_export);
int						handle_redirection(t_ast *root, int *i, int *fd_out,
							int *fd_in);
int						setup_redirections(t_ast *root, t_exaction *data,
							int fd_out, int fd_in);
int						handle_redirection_utils(t_ast *root, int *i,
							int *fd_in);

#endif
