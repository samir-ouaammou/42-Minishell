#include "../minishell.h"

void free_split(char **split)
{
    int i;
    if (!split)
        return;
    i = 0;
    while (split[i])
    {
        // free(split[i]);
        split[i] =  NULL;
        i++;
    }
    // free(split);
    split = NULL;
}

int count_words(char *str)
{
    int count = 0;
    int i = 0;
    char c = '\0';

    while (str[i])
    {
        while (str[i] == ' ') 
            i++;
        if (str[i] == '\0')
            break;
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
    return count;
}

char **ft_split_quots(char *str)
{
    char **res;
    char c;
    int i = 0, j = 0, k, h;

    if (!str)
        return (NULL);
    
    int word_count = count_words(str);
    res = malloc((word_count + 1) * sizeof(char *));
    if (!res)
        return (NULL);

    while (str[i])
    {
        while (str[i] == ' ') 
            i++;
        if (str[i] == '\0')
            break;

        c = '\0';
        k = i;

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

        res[j] = malloc((i - k + 1) * sizeof(char)); 
        if (!res[j])
        {
            // free_split(res);
            return (NULL);
        }

        h = 0;
        while (k < i)
            res[j][h++] = str[k++];
        res[j++][h] = '\0';
    }
    res[j] = NULL;
    return (res);
}

char *ft_str_join(char **str, t_exaction *data, short bol)
{
    int i, j, k, len;
    char *res, *tmp;

    if (!str || !str[0])
        return (NULL);
    i = 0;
    k = 0;
    len = 0;
    while (str[i])
    {
        if (str[i][0] != 39)
        {
            if (str[i][0] == 34)
            {
                str[i][strlen(str[i]) - 1] = '\0';
                tmp = strdup(&str[i][1]);
                if (!tmp)
                {
                    // free_split(str);
                    return (NULL);
                }
                // free(str[i]);
                str[i] = tmp;
            }
            if (bol)
                str[i] = process_strings(str[i], data);
        }
        else
        {
            str[i][strlen(str[i]) - 1] = '\0';
            tmp = strdup(&str[i][1]);
            if (!tmp)
            {
                // free_split(str);
                return (NULL);
            }
            // free(str[i]);
            str[i] = tmp;
        }
        len += strlen(str[i]);
        i++;
    }
    res = malloc((len + 1) * sizeof(char));
    if (!res)
    {
        // free_split(str);
        return (NULL);
    }
    i = 0;
    while (str[i])
    {
        j = 0;
        while (str[i][j])
            res[k++] = str[i][j++];
        i++;
    }
    res[k] = '\0';
    // free_split(str);
    return (res);
}

void ft_remove_quots(char **str, t_exaction *data, short bol)
{
    int i;
    char **split;

    if (!str || !str[0])
        return;
    i = 0;
    while (str[i])
    {
        split = ft_split_quots(str[i]);
        if (!split)
            return;
        // free(str[i]);
        str[i] = ft_str_join(split, data, bol);
        i++;
    }
}
