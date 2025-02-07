#include "../../minishell.h"

int ft_isalnum(int c)
{
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'));
}

char	*ft_strncpy(char *dest, char *src, int n)
{
    int	i;

	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}

int builtin_echo(char **str, t_data *data)
{
    (void)data;
    int i = 1;
    int quots = 2;
    int newline = 0;
    int check = 0;
    char *value = NULL;

    if (!str || !str[0])
        return (0);
    while (str[i] && ft_strcmp(str[i], "-n") == 0)
    {
        check = 1;
        i++;
    }
    while (str[i])
    {
        char *ss = ft_check_quots(str[i], &quots, &newline, data);
        if (!ss)
            return (-1);
        if (quots == 1)
            ft_putstr_fd(ss, 1);
        else if (quots == 2)
        {
            int j = 0;
            while (ss[j])
            {
                if (ss[j] == '$' && ss[j + 1] == '?')
                {
                    ft_putnbr_fd(data->exit_status, 1);
                    j += 2;
                }
                else if (ss[j] == '$')
                {
                    j++;
                    int count = 0;
                    while (ss[j + count] && ft_isalnum(ss[j + count]))
                        count++;
                    char *res = malloc(sizeof(char) * (count + 1));
                    if (!res)
                        return (-1);
                    ft_strncpy(res, &ss[j], count);
                    res[count] = '\0';
                    value = getenv(res);
                    if (value)
                        ft_putstr_fd(value, 1);
                    else
                        ft_putstr_fd("", 1);
                    j += count;
                }
                else
                {
                    ft_putchar_fd(ss[j], 1);
                    j++;
                }
            }
        }
        if (newline && str[i + 1])
            ft_putchar_fd(' ', 1);
        i++;
    }

    if (!check)
        ft_putchar_fd('\n', 1);
    return (1);
}