/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: aahaded <marvin@42.fr>                     +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/11/12 13:34:09 by aahaded           #+#    #+#             */
/*   Updated: 2024/11/12 18:37:17 by aahaded          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

static char	*ft_strchar(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == c)
			return (str + i);
		i++;
	}
	if (c == '\0')
		return (str + i);
	return (0);
}

static void	ft_lkmala_strjoin(char *res, char *str, int *len)
{
	int	i;

	i = 0;
	while (str[i])
	{
		res[*len] = str[i];
		i++;
		(*len)++;
	}
}

static char	*ft_strjoin(char *s1, char *s2)
{
	int		len;
	char	*res;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";
	res = malloc(ft_strlenw(s1) + ft_strlenw(s2) + 1);
	if (!res)
		return (NULL);
	len = 0;
	ft_lkmala_strjoin(res, s1, &len);
	ft_lkmala_strjoin(res, s2, &len);
	res[len] = '\0';
	return (res);
}

static char	*ft_read_to_saved(int fd, char *saved)
{
	char	*buffer;
	char	*temp;
	int		bytes_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free(saved), NULL);
	while (!ft_strchar(saved, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(buffer), free(saved), NULL);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(saved, buffer);
		if (!temp)
			return (free(buffer), free(saved), NULL);
		free(saved);
		saved = temp;
	}
	free(buffer);
	return (saved);
}

char	*get_next_line(int fd)
{
	static char	*saved;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free(saved), NULL);
	saved = ft_read_to_saved(fd, saved);
	if (!saved)
		return (NULL);
	return (ft_lkmala(&saved));
}
