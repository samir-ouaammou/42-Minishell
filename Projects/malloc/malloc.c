/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaammo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 01:07:00 by souaammo          #+#    #+#             */
/*   Updated: 2025/03/08 01:07:02 by souaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"
#include "malloc.h"

void	*ft_alloc(size_t size, char c)
{
	static t_malloc	*head;
	t_malloc		*new_node;

	if (c == 'M')
	{
		new_node = ft_lst_new(size);
		if (!new_node)
			return (NULL);
		ft_lst_add_back(&head, new_node);
		return (new_node->ptr);
	}
	else if (c == 'F')
		free_all_memory(&head);
	return (NULL);
}

void	*ft_malloc(size_t size)
{
	return (ft_alloc(size, 'M'));
}

void	ft_exit(int status)
{
	ft_alloc(0, 'F');
	exit(status);
}
