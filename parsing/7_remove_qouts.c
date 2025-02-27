#include "../minishell.h"

void free_split(char **split)
{
    int i = 0;
    if (!split)
        return;
    while (split[i])
        free(split[i++]);
    free(split);
}

char **ft_split_quots(char *str)
{
    char **res;
    char c;
    int i, j, k, h;

    if (!str)
        return (NULL);
    res = malloc(strlen(str) * sizeof(char *));
    if (!res)
        return (NULL);
    i = 0;
    j = 0;
    while (str[i])
    {
        c = '\0';
        res[j] = malloc(strlen(str) + 1);
        if (!res[j])
        {
            free_split(res);  // تحرير كل ما تم تخصيصه سابقًا
            return (NULL);
        }
        if (str[i] == 39 || str[i] == 34)
        {
            k = i;
            c = str[i++];
            while (str[i] && str[i] != c)
                i++;
            if (str[i])
                i++;
        }
        else
        {
            k = i;
            while (str[i] && str[i] != 39 && str[i] != 34)
                i++;
        }
        h = 0;
        while (k < i)
            res[j][h++] = str[k++];
        res[j++][h] = '\0';
    }
    res[j] = NULL;
    return (res);
}

char *ft_str_join(char **str, t_data *data)
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
                    free_split(str);
                    return (NULL);
                }
                free(str[i]); // تحرير الذاكرة القديمة
                str[i] = tmp;
            }
            str[i] = process_strings(str[i], data);
        }
        else
        {
            str[i][strlen(str[i]) - 1] = '\0';
            tmp = strdup(&str[i][1]);
            if (!tmp)
            {
                free_split(str);
                return (NULL);
            }
            free(str[i]); // تحرير الذاكرة القديمة
            str[i] = tmp;
        }
        len += strlen(str[i]);
        i++;
    }
    res = malloc((len + 1) * sizeof(char));
    if (!res)
    {
        free_split(str);
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
    free_split(str);  // تحرير المصفوفة بأكملها
    return (res);
}

void ft_remove_quots(char **str, t_data *data)
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
        free(str[i]); // تحرير القديم قبل الاستبدال
        str[i] = ft_str_join(split, data);
        i++;
    }
}
