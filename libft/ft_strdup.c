#include "libft.h"

char	*ft_strdup(const char *str)
{
	size_t	i;
	char	*res;

	res = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
