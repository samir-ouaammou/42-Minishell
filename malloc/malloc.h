#ifndef FT_MALLOC_H
# define FT_MALLOC_H

#include <stdlib.h>

typedef struct s_malloc
{
    void            *ptr;
    struct s_malloc *next;
}                   t_malloc;

void                ft_exit(int status);
void                *ft_malloc(size_t size);
t_malloc            *ft_lst_new(size_t size);
void                free_all_memory(t_malloc **head);
void                ft_lst_add_back(t_malloc **head, t_malloc *new);

#endif 