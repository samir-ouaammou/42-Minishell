#include "../minishell.h"

int ft_is(char c)
{
    if (c == '<' || c == '>' || c == '|' || c == '&')
        return (1);
    return (0);
}

void ft_here_doc(t_parsing *shell, char *str)
{
    char    *line;
    char    **stop;
    char    *name;
    char    c;
    int     i;
    int     j;
    int     fd;
    int     nbr;

    if (!str || !str[0])
        return ;

    i = 0;
    nbr = 1;
    stop = malloc(sizeof(char *) * 2);
    stop[1] = NULL;
    while (str[i])
    {
        if (str[i] == 34 || str[i] == 39)
        {
            c = str[i++];
            while (str[i] && str[i] != c)
                i++;
            if (str[i])
                i++;
        }
        else if (str[i] == '<' && str[i + 1] == '<')
        {
            i += 2;
            c = ' ';
            while (str[i] && str[i] == ' ')
                i++;
            if (ft_is(str[i]))
                ft_free_args(shell);
            j = i;
            while (str[j] && str[j] != ' ' && !ft_is(str[j]))
            {
                if (str[j] == 34 || str[j] == 39)
                {
                    c = str[j++];
                    while (str[j] && str[j] != c)
                        j++;
                    if (c == str[j])
                        c = ' ';
                }
                if (str[j])
                    j++;
            }
            if (!str[j] && c != ' ')
            {
                while (1)
                {
                    line = readline("heredoc> ");
                    free(line);
                }
            }
            else
            {
                stop[0] = ft_substr(str, i, j - i);
                ft_remove_quots(stop);

                name = ft_strjoin("/tmp/heredoc", ft_itoa(nbr));
                fd = open(name, O_CREAT | O_RDWR | O_TRUNC, 0644);
                while(1)
                {
                    line = readline("heredoc> ");
                    if (!line || !line[0])
                        break;
                    if (!strcmp(stop[0], line))
                        break;
                    write(fd, line, ft_strlen(line));
                    write(fd, "\n", 1);
                    free(line);
                }
                if(line)
                    free(line);
            }
            i = j;
            while (str[j] && str[j] == ' ')
                j++;
            if (str[j] && (str[j] == '>' || str[j] == '|' || str[j] == '&'))
            {
                free(stop[0]);
                nbr++;
            }
        }
        else
            i++;
    }
    free(stop[0]);
    free(stop);
}

