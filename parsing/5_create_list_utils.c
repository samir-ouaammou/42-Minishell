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

t_list	*ft_creat_new_node(t_parsing *shell, int start, int end)
{
	t_list	*new;

	new = ft_malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->value = ft_malloc((end - start + 2) * sizeof(char *));
	if (!new->value)
		return (NULL);
	shell->len = 0;
	while (start <= end)
	{
		new->value[shell->len] = ft_strdup(shell->temp[start]);
		shell->len++;
		start++;
	}
	new->value[shell->len] = NULL;
	new->next = NULL;
	return (new);
}
