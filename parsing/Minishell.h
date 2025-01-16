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
	char	**cmds_split;

}			t_parsing;

void		ft_parsing(t_parsing *shell);
void		ft_free_all(t_parsing *shell);
void		ft_parentheses(t_parsing *shell);
void		ft_delete_commits(t_parsing *shell);
int			ft_check_operators(t_parsing *shell);
void		ft_check_syntax_errors(t_parsing *shell);
void		ft_check_remaining_errors(t_parsing *shell);

#endif
