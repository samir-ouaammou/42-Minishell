/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghlimi <aghlimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 11:45:10 by aghlimi           #+#    #+#             */
/*   Updated: 2025/02/09 08:23:28 by aghlimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_H
# define GC_H

# include <stdlib.h>

typedef struct s_gc
{
	void		*ptr;
	struct s_gc	*next;
	struct s_gc	*prev;
}				t_gc;

t_gc	*gc_alloc(size_t size);
void	gc_clean(t_gc *head);
void	gc_free(t_gc **head, void *ptr);
t_gc	*last_gc(t_gc *head);
void	add_gc(t_gc **head, t_gc *new);
void* ft_malloc(size_t size);
void	*gc(size_t size, char flag, void *ptr);
void ft_exit(int);
#endif 