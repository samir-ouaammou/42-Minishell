#include "../minishell.h"

char	*ft_clean_string(char *str)
{
	char	*tmp;

	if (str[0] == 39 || str[0] == 34)
	{
		str[ft_strlen(str) - 1] = '\0';
		tmp = ft_strdup(&str[1]);
		if (!tmp)
			return (NULL);
		return (tmp);
	}
	return (str);
}

int	ft_calculate_length(char **str, t_exaction *data, short bol)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i][0] != 39 && bol)
			str[i] = process_strings(str[i], data);
		str[i] = ft_clean_string(str[i]);
		len += ft_strlen(str[i]);
		i++;
	}
	return (len);
}

char	*ft_str_join(char **str, t_exaction *data, short bol)
{
	char	*res;
	int		i;
	int		j;
	int		k;
	int		len;

	if (!str || !str[0])
		return (NULL);
	len = ft_calculate_length(str, data, bol);
	res = ft_malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	k = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
			res[k++] = str[i][j++];
		i++;
	}
	res[k] = '\0';
	return (res);
}

void	ft_remove_quots(char **str, t_exaction *data, short bol)
{
	int		i;
	char	**res;
	char	**split;

	if (!str || !str[0])
		return ;
	res = NULL;
	i = 0;
	while (str[i])
	{
		split = ft_split_quots(str[i], res, 0, 0);
		if (!split)
			return ;
		str[i] = ft_str_join(split, data, bol);
		i++;
	}
}

int	count_words(char *str, int count, int i, char c)
{
	count = 0;
	i = 0;
	c = '\0';
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (str[i] == '\0')
			break ;
		count++;
		if (str[i] == '\'' || str[i] == '"')
		{
			c = str[i++];
			while (str[i] && str[i] != c)
				i++;
			if (str[i])
				i++;
		}
		else
		{
			while (str[i] && str[i] != ' ' && str[i] != '\'' && str[i] != '"')
				i++;
		}
	}
	return (count);
}
