#include "../minishell.h"

int	check_special_chars(char **args)
{
	int(i), (j);
	i = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (args[i][j] == '$' && args[i][j + 1] == '\0')
				return (0);
			else if (args[i][j] == '*')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
