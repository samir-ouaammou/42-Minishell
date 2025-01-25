#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_parsing
{
	int		i;
	int		j;
	int		bol;
	int		len;
	int		free;
	int		parentheses;
	char	chr;
	char	*cmds;
	char	*input;
	char	**tokens;

}			t_parsing;

void		ft_parsing(t_parsing *shell);
void		ft_free_all(t_parsing *shell);
void		ft_split_args(t_parsing *shell);
void		ft_skip_string(t_parsing *shell);
void		ft_count_len_args(t_parsing *shell);
void		ft_check_syntax_errors(t_parsing *shell);
int			ft_check_single_operators(t_parsing *shell);
int			ft_check_double_operators(t_parsing *shell);
void		ft_check_operator_position(t_parsing *shell);

#endif
