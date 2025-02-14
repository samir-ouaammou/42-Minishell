#include "../minishell.h"

char *ft_compress_wildcards(const char *input)
{
    char    *res;
    int     i;
    int     j;

    if (!input || !input[0])
        return (NULL);
    res = (char *)malloc(ft_strlen(input) + 1);
    if (!res)
        return (NULL);
    i = 0;
    j = 0;
    while (input[i] != '\0')
    {
        if (input[i] == '*')
        {
            if (j == 0 || res[j - 1] != '*')
                res[j++] = '*';
        }
        else
            res[j++] = input[i];
        i++;
    }
    res[j] = '\0';
    return res;
}

int ft_match_pattern(const char *wildcard, const char *filename)
{
    int i = 0;
    int j = 0;
    int star_i = -1;
    int star_j = -1;

    if (!wildcard || !wildcard[0] || !filename || !filename[0])
        return 0;
    wildcard = ft_compress_wildcards(wildcard);
    if (!wildcard || !wildcard[0])
        return (0);
    if (ft_strcmp(wildcard, "*") == 0)
        return (filename[0] != '.');
    if (ft_strcmp(wildcard, ".*") == 0)
        return (1);
    if (ft_strcmp(wildcard, "*.") == 0)
        return (0);

    while (filename[j] != '\0')
    {
        if (wildcard[i] == '*')
        {
            star_i = i;
            star_j = j;
            i++;
        }
        else if (wildcard[i] == filename[j])
        {
            i++;
            j++;
        }
        else if (star_i != -1)
        {
            i = star_i + 1;
            star_j++;
            j = star_j;
        }
        else
            return 0;
    }

    while (wildcard[i] == '*')
        i++;
    return (wildcard[i] == '\0' && filename[j] == '\0' && (wildcard[0] == '.' || filename[0] != '.'));
}
