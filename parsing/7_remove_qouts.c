#include "../minishell.h"


char    **ft_split_quots(char *str)
{
    char    **res;
    char    c;
    int     i;
    int     j;
    int     k;
    int     h;

    if (!str)
        return (NULL);
    res = malloc (strlen(str) * sizeof(char *));
    i = 0;
    j = 0;
    while (str[i])
    {
        c = '\0';
        res[j] = malloc(strlen(str) + 1);
        if (str[i] == 39 || str[i] == 34)
        {
            k = i;
            c = str[i++];
            while (str[i] && str[i] != c)
                i++;
            if (str[i])
                i++;
        }
        else if (str[i] != 39 && str[i] != 34)
        {
            k = i;
            while (str[i] && str[i] != 39 && str[i] != 34)
                i++;
        }
        h = 0;
        while (k < i)
        {
            res[j][h] = str[k];   //    
            k++;
            h++;
        }
        res[j++][h] = '\0';
    }
    res[j++] = NULL;
    return (res);
}

char    *ft_str_join(char **str, t_data *data)
{
    int     i;
    int     j;
    int     k;
    int     len;
    char    *res;
    char    *tmp;

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
                free(str[i]);
                str[i] = tmp;
            }
            str[i] = process_template_string(str[i], data);
        } 
        else if (str[i][0] == 39)
        {
            str[i][strlen(str[i]) - 1] = '\0';
            tmp = strdup(&str[i][1]);
            free(str[i]);
            str[i] = tmp;
        }
        len += strlen(str[i]);
        i++;
    }
    res = malloc((len + 1) * sizeof(char));
    i = 0;
    while (str[i])
    {
        j = 0;
        while (str[i][j])
        {
            res[k++] = str[i][j];
            j++;
        }
        i++;
    }
    res[k] = '\0';
    return (res);
}

void ft_remove_quots(char **str, t_data *data)
{
    int     i;
    char    **split;

    if (!str || !str[0])
        return ;
    i = 0;
    while (str[i])
    {
        // printf("[%s] ", str[i]); // TMP
        split = ft_split_quots(str[i]);
        free(str[i]);
        str[i] = ft_str_join(split, data);
        // printf("=> {%s}\n", str[i]); // TMP
        i++;
    }

}
// void    ft_remove_tab(char **str)
// {
//     int     i;
//     int     j;
//     int     k;

//     if (!str || !str[0])
//         return ;
//     i = 0;
//     while (str[i])
//     {
//         j = 0;
//         while (str[i][j])
//         {
//             if (str[i][j] == '\t')
//             {
//                 k = j;
//                 while (str[i][k])
//                 {
//                     str[i][k] = str[i][k + 1];
//                     k++;
//                 }
//             }
//             else
//                 j++;
//         }
//         i++;
//     }
// }

// char    **ft_split_quots(char *str)
// {
//     char    **res;
//     char    c;
//     int     i;
//     int     j;
//     int     k;
//     int     h;

//     if (!str)
//         return (NULL);
//     res = malloc (strlen(str) * sizeof(char *));
//     i = 0;
//     j = 0;
//     while (str[i])
//     {
//         res[j] = malloc(strlen(str) + 1);
//         if (str[i] == 39 || str[i] == 34)
//         {
//             k = i;
//             c = str[i++];
//             while (str[i] && str[i] != c)
//                 i++;
//             if (str[i])
//                 i++;
//         }
//         else if (str[i] != 39 && str[i] != 34)
//         {
//             k = i;
//             while (str[i] && str[i] != 39 && str[i] != 34)
//                 i++;
//         }
//         h = 0;
//         while (k < i)
//         {
//             res[j][h] = str[k];
//             k++;
//             h++;
//         }
//         res[j++][h] = '\0';
//     }
//     res[j++] = NULL;
//     return (res);
// }
