#include "../minishell.h"
#include "malloc.h"

void	ft_lst_add_back(t_malloc **head, t_malloc *new)
{
	t_malloc	*temp;

	if (!new)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

t_malloc	*ft_lst_new(size_t size)
{
	t_malloc	*new_node;
	void		*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	new_node = malloc(sizeof(t_malloc));
	if (!new_node)
		return (free(ptr), NULL);
	new_node->ptr = ptr;
	new_node->next = NULL;
	return (new_node);
}

void	free_all_memory(t_malloc **head)
{
	t_malloc	*temp;
	t_malloc	*help;

	temp = *head;
	while (temp)
	{
		help = temp;
		temp = temp->next;
		if (help->ptr)
			free(help->ptr);
		free(help);
	}
}
