
#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!big && little)
		return (NULL);
	if (!*little)
		return ((char *)big);
	while (big[i])
	{
		while (big[i + j] == little[j] && big[i + j])
		{
			j++;
			if (little[j] == '\0')
				return ((char *) big + i);
		}
		i++;
		j = 0;
	}
	return (NULL);
}