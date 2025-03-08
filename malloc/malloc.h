/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaammo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 01:07:16 by souaammo          #+#    #+#             */
/*   Updated: 2025/03/08 01:07:18 by souaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <stdlib.h>

typedef struct s_malloc
{
	void			*ptr;
	struct s_malloc	*next;
}					t_malloc;

void				ft_exit(int status);
void				*ft_malloc(size_t size);
t_malloc			*ft_lst_new(size_t size);
void				free_all_memory(t_malloc **head);
void				ft_lst_add_back(t_malloc **head, t_malloc *new);

#endif
