#include "../minishell.h"


int ft_check_is_operators(char *str)
{
    if (!str || !str[0])
        return (0);

    return (!ft_strcmp(str, "|")
        || !ft_strcmp(str, "||") || !ft_strcmp(str, "&&")
        || !ft_strcmp(str, "(") || !ft_strcmp(str, ")"));
}

int ft_check_is_redirections(char *str)
{
    if (!str || !str[0])
        return (0);

    return (!ft_strcmp(str, "<") || !ft_strcmp(str, ">")
        || !ft_strcmp(str, "<<") || !ft_strcmp(str, ">>"));
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