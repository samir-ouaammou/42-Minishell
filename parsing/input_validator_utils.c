/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validator_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaammo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 01:03:43 by souaammo          #+#    #+#             */
/*   Updated: 2025/03/08 01:03:45 by souaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_redirections(t_parsing *shell, int index)
{
	if (!shell->temp[index])
		return (0);
	if (!ft_strcmp(shell->temp[index], "<")
		|| !ft_strcmp(shell->temp[index], ">")
		|| !ft_strcmp(shell->temp[index], ">>")
		|| !ft_strcmp(shell->temp[index], "<<"))
		return (1);
	return (0);
}

int	ft_is_logical_operators(t_parsing *shell, int index)
{
	if (!shell->temp[index])
		return (0);
	if (!ft_strcmp(shell->temp[index], "|")
		|| !ft_strcmp(shell->temp[index], "&")
		|| !ft_strcmp(shell->temp[index], "||")
		|| !ft_strcmp(shell->temp[index], "&&"))
		return (1);
	return (0);
}

void	ft_remainder_of_this_function(t_parsing *shell)
{
	if ((!ft_strcmp(shell->temp[shell->i], "(")
			&& (ft_is_logical_operators(shell, shell->i + 1)))
		|| (!ft_strcmp(shell->temp[shell->i + 1], ")")
			&& (ft_is_logical_operators(shell, shell->i)
				|| ft_is_redirections(shell, shell->i)))
		|| (!ft_strcmp(shell->temp[shell->i], "(")
			&& !ft_strcmp(shell->temp[shell->i + 1], ")"))
		|| (!ft_strcmp(shell->temp[shell->i + 1], "|")
			&& (ft_is_logical_operators(shell, shell->i)
				|| ft_is_redirections(shell, shell->i))))
		ft_free_args(shell);
}

char	*ft_strjoin_and_free(char *s1, const char *s2)
{
	char	*res;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	res = ft_malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!res)
		return (NULL);
	while (s1[++i])
		res[i] = s1[i];
	while (s2[j])
	{
		res[i + j] = s2[j];
		j++;
	}
	res[i + j] = '\0';
	return (res);
}

void	ft_check_operator_position(t_parsing *shell)
{
	if (shell->free == -1 ||!shell->temp || !shell->temp[0])
		return ;
	shell->i = 0;
	while (shell->temp && shell->temp[shell->i])
	{
		if ((shell->i == 0 && ft_is_logical_operators(shell, 0))
			|| (!shell->temp[shell->i + 1]
				&& (ft_is_logical_operators(shell, shell->i)
					|| ft_is_redirections(shell, shell->i)))
			|| ((ft_is_logical_operators(shell, shell->i))
				&& (ft_is_logical_operators(shell, shell->i + 1)))
			|| ((ft_is_redirections(shell, shell->i))
				&& (ft_is_redirections(shell, shell->i + 1)))
			|| (!ft_strcmp(shell->temp[shell->i], "&")))
		{
			ft_free_args(shell);
			return ;
		}
		else if (shell->temp[shell->i] && shell->temp[shell->i + 1])
			ft_remainder_of_this_function(shell);
		shell->i++;
	}
}
