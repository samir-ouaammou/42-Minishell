#include "libft.h"

char *ft_strrstr(const char *haystack, const char *needle)
{
    char *last = NULL;
    char *current = (char *)haystack;

    if (!*needle)
        return (char *)haystack;
    while ((current = strstr(current, needle)) != NULL)
    {
        last = current;
        current++;
    }
    return (last);
}