#include "./libft.h"

char *ft_strncpy(char *dest, const char *src, int len)
{
    int i;

    i = 0;
    while (src[i] && i < len)
    {
        dest[i] = src[i];
        i++;
    }
    return (dest);
}