/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahaded <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 00:00:18 by aahaded           #+#    #+#             */
/*   Updated: 2025/03/08 00:00:19 by aahaded          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(char **value)
{
	int		i;
	char	**copy;
	t_list	*new_node;

	i = 0;
	new_node = (t_list *)ft_malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	else
		i = 0;
	while (value[i])
		i++;
	copy = ft_malloc((i + 1) * sizeof(char *));
	if (!copy)
		return (NULL);
	i = 0;
	while (value[i])
	{
		copy[i] = ft_strdup(value[i]);
		i++;
	}
	copy[i] = NULL;
	new_node->value = copy;
	new_node->next = NULL;
	return (new_node);
}
