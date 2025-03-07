#include "../minishell.h"

static void	ft_process_next_node(t_list *list, char **redirections)
{
	int	i;

	i = 0;
	while (list->next->value[++i])
	{
		*redirections = ft_strjoin_and_free
			(*redirections, list->next->value[i]);
		*redirections = ft_strjoin_and_free(*redirections, " ");
		list->next->value[i] = NULL;
	}
}

static void	ft_process_current_node(t_list *list, char **redirections)
{
	int	i;

	i = -1;
	while (list->value[++i])
	{
		*redirections = ft_strjoin_and_free(*redirections, list->value[i]);
		*redirections = ft_strjoin_and_free(*redirections, " ");
		list->value[i] = NULL;
	}
}

static void	ft_process_help_list(t_list *help, char **redirections)
{
	int	i;

	while (help)
	{
		if (help && help->value && ft_check_is_operators(help->value[0]))
			break ;
		i = 0;
		while (help->value && help->value[i])
		{
			*redirections = ft_strjoin_and_free(*redirections, help->value[i]);
			*redirections = ft_strjoin_and_free(*redirections, " ");
			i++;
		}
		help = help->next;
	}
}

static void	ft_process_list(t_list *list, char **redirections, int *j, int *k)
{
	while (list)
	{
		if (list && list->value && ft_check_is_operators(list->value[0]))
			break ;
		if (list && list->next && list->next->value[1]
			&& ft_check_is_redirections(list->value[0])
			&& !ft_check_is_redirections(list->next->value[0]))
		{
			ft_process_next_node(list, redirections);
			(*j)++;
		}
		else if ((list && list->value[1]
				&& !ft_check_is_operators(list->value[0])
				&& !ft_check_is_redirections(list->value[0]))
			|| (list && *j == 0 && *k == 0 && list->next
				&& !list->next->value[1]
				&& !ft_check_is_redirections(list->value[0])))
		{
			ft_process_current_node(list, redirections);
			(*j)++;
		}
		if (list)
			list = list->next;
		(*k)++;
	}
}

char	*ft_move_flags(t_parsing *shell, t_list *list)
{
	t_list	*help;
	char	*redirections;
	int		j;
	int		k;

	redirections = ft_malloc(ft_strlen(shell->input) + 1);
	if (!redirections)
		return (NULL);
	redirections[0] = '\0';
	j = 0;
	k = 0;
	help = list;
	ft_process_list(list, &redirections, &j, &k);
	ft_process_help_list(help, &redirections);
	redirections[ft_strlen(redirections) - 1] = '\0';
	return (redirections);
}
