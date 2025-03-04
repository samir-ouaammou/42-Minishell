/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghlimi <aghlimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 11:25:59 by aghlimi           #+#    #+#             */
/*   Updated: 2025/02/08 11:27:14 by aghlimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

t_gc	*gc_alloc(size_t size)
{
	void	*ptr;
	t_gc	*node;

	ptr = malloc(size);
	if (ptr == NULL)
	{
		return (NULL);
	}
	node = malloc(sizeof(t_gc));
	if (node == NULL)
	{
		free(ptr);
		return (NULL);
	}
	node->ptr = ptr;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	gc_clean(t_gc *head)
{
	t_gc	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head->ptr);
		free(head);
		head = tmp;
	}
}

void	gc_free(t_gc **head, void *ptr)
{
	t_gc	*ft_head;

	ft_head = *head;
	while (ft_head)
	{
		if (ft_head->ptr == ptr)
		{
			free(ptr);
			if (ft_head->prev)
			{
				ft_head->prev->next = ft_head->next;
			}
			else
			{
				*head = ft_head->next;
			}
			free(head);
			return ;
		}
		ft_head = ft_head->next;
	}
}

t_gc	*last_gc(t_gc *head)
{
	while (head && head->next)
	{
		head = head->next;
	}
	return (head);
}

void	add_gc(t_gc **head, t_gc *new)
{
	t_gc	*last_node;

	last_node = last_gc(*head);
	if (last_node)
	{
		last_node->next = new;
		new->prev = last_node;
	}
	else
	{
		*head = new;
	}
}
