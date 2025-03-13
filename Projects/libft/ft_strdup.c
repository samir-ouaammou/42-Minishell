/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahaded <aahaded@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 19:36:38 by aahaded           #+#    #+#             */
/*   Updated: 2025/02/26 21:48:15 by souaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		str_len;
	char	*res;

	if (!s)
		return (NULL);
	str_len = ft_strlen(s);
	res = ft_malloc(str_len + 1);
	if (res == NULL)
		return (NULL);
	ft_strlcpy(res, s, str_len + 1);
	return (res);
}
