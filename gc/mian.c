/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mian.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghlimi <aghlimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 11:27:35 by aghlimi           #+#    #+#             */
/*   Updated: 2025/02/09 08:25:18 by aghlimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

void	*gc(size_t size, char flag, void *ptr)
{
	static t_gc	*gc_head = NULL;
	t_gc		*node;

	if (flag == 'm')
	{
		node = gc_alloc(size);
		if (node == NULL)
			return (NULL);
		add_gc(&gc_head, node);
		return node->ptr;
	}
	else if (flag == 'f')
	{
		gc_clean(gc_head);
	}
	else if (flag == 'o')
	{
		gc_free(&gc_head, ptr);
	}
	return NULL;
}
void ft_exit(int status)
{
	gc(0,'f',NULL);
	exit(status);
}
void* ft_malloc(size_t size)
{
	void * l = gc(size,'m',NULL);
	return l;
}

