/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_qouts_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaammo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 01:04:34 by souaammo          #+#    #+#             */
/*   Updated: 2025/03/08 01:04:36 by souaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

void	ft_free_parsing(t_parsing *shell)
{
	if (shell->free != -1)
		ft_free_args(shell);
}

void	ft_free_args(t_parsing *shell)
{
	if (!shell || shell->free == -1)
		return ;
	shell->free = -1;
}

char	**ft_allocate_result(char *str)
{
	char	**res;
	int		word_count;

	if (!str)
		return (NULL);
	word_count = count_words(str, 0, 0, '\0');
	res = ft_malloc((word_count + 1) * sizeof(char *));
	return (res);
}

void	ft_extract_word(char *str, int *i, char *c)
{
	if (str[*i] == '\'' || str[*i] == '"')
	{
		*c = str[(*i)++];
		while (str[*i] && str[*i] != *c)
			(*i)++;
		if (str[*i])
			(*i)++;
	}
	else
	{
		while (str[*i] && str[*i] != ' ' && str[*i] != '\'' && str[*i] != '"')
			(*i)++;
	}
}

char	**ft_split_quots(char *str, char **res, int i, int j)
{
	char	c;
	int		k;
	int		h;

	res = ft_allocate_result(str);
	if (!res)
		return (NULL);
	while (res && str[i])
	{
		while (str[i] == ' ')
			i++;
		if (str[i] == '\0')
			break ;
		c = '\0';
		k = i;
		ft_extract_word(str, &i, &c);
		res[j] = ft_malloc((i - k + 1) * sizeof(char));
		if (!res[j])
			return (NULL);
		h = 0;
		while (k < i)
			res[j][h++] = str[k++];
		res[j++][h] = '\0';
	}
	return (res[j] = NULL, res);
}
