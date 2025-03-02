/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_cleanup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaammo <souaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:47:55 by aahaded           #+#    #+#             */
/*   Updated: 2025/03/02 16:12:42 by souaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    free_all(char **args)
{
    if (!args)
        return;
    int i = 0;
    while (args[i])
    {
        free(args[i]);
        i++;
    }
    free(args);
}
