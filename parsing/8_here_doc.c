#include "../minishell.h"

int ft_is(char c)
{
    if (c == '<' || c == '>' || c == '|' || c == '&')
        return (1);
    return (0);
}

void ft_move_input(t_parsing *shell, char *str)
{
    if (!shell || !str)
        return ;
    shell->help = NULL;
    shell->i = 0;
    shell->j = 0;
    shell->nbr = 1;
    while (str[shell->i])
    {
        if (str[shell->i] == '\t')
        {
            shell->j++;
            while (str[shell->i] && str[shell->i] == '\t')
                shell->i++;
        }
        shell->i++;
    }
    if (shell->j == 0)
        return;
    shell->help = malloc(ft_strlen(str) + (shell->j * 15) + 1);
    if (!shell->help)
        return ;
    shell->j = 0;
    shell->i = 0;
    while (str[shell->i])
    {
        if (str[shell->i] == '\t')
        {
            shell->itoa = ft_itoa(shell->nbr);
            shell->name = ft_strjoin("/tmp/heredoc", shell->itoa);
            free(shell->itoa);

            while (str[shell->i] && str[shell->i] == '\t')
                shell->i++;
            shell->len = 0;
            while (shell->name[shell->len])
            {
                shell->help[shell->j++] = shell->name[shell->len];
                shell->len++;
            }
            free(shell->name);
            shell->nbr++;
        }
        shell->help[shell->j++] = str[shell->i];
        shell->i++;
    }
    free(shell->input);
    shell->help[shell->j] = '\0';
    shell->input = shell->help;
}


void ft_here_doc(t_parsing *shell, char *str)
{
    if (!str || !str[0])
        return ;

    shell->i = 0;
    shell->bol = 0;
    shell->nbr = 1;
    shell->start = 0;
    shell->end = 0;
    shell->stop = malloc(sizeof(char *) * 2);
    if (!shell->stop)
        return ;
    shell->stop[1] = NULL;
    while (str[shell->i])
    {
        if (str[shell->i] == 34 || str[shell->i] == 39)
        {
            shell->chr = str[shell->i++];
            while (str[shell->i] && str[shell->i] != shell->chr)
                shell->i++;
            if (str[shell->i])
                shell->i++;
        }
        else if (str[shell->i] == '<' && str[shell->i + 1] == '<')
        {
            shell->i += 2;
            shell->chr = ' ';
            while (str[shell->i] && (str[shell->i] == ' ' /*|| str[shell->i] == '\n'*/))
                shell->i++;
            if (ft_is(str[shell->i]) || !str[shell->i])
            {
                ft_free_args(shell);
                free(shell->stop);
                return ;
            }
            if (shell->bol == 0)
                shell->start = shell->i;
            shell->bol = 1;
            shell->j = shell->i;
            while (str[shell->j] && str[shell->j] != ' ' && !ft_is(str[shell->j]))
            {
                if (str[shell->j] == 34 || str[shell->j] == 39)
                {
                    shell->chr = str[shell->j++];
                    while (str[shell->j] && str[shell->j] != shell->chr)
                        shell->j++;
                    if (shell->chr == str[shell->j])
                        shell->chr = ' ';
                }
                if (str[shell->j])
                    shell->j++;
            }
            if (!str[shell->j] && shell->chr != ' ')
            {
                while (1)
                {
                    shell->line = readline("heredoc> ");
                    free(shell->line);
                }
            }
            else
            {
                shell->stop[0] = ft_substr(str, shell->i, shell->j - shell->i);
                ft_remove_quots(shell->stop);
                shell->itoa = ft_itoa(shell->nbr);
                shell->name = ft_strjoin("/tmp/heredoc", shell->itoa);
                free(shell->itoa);
                shell->fd = open(shell->name, O_CREAT | O_RDWR | O_TRUNC, 0644);
                while (1)
                {
                    shell->line = readline("heredoc> ");
                    if (!shell->line)
                        break;
                    if (!strcmp(shell->stop[0], shell->line))
                    {
                        free(shell->line);
                        break;
                    }
                    write(shell->fd, shell->line, ft_strlen(shell->line));
                    write(shell->fd, "\n", 1);
                    free(shell->line);
                }
                close(shell->fd);
                free(shell->name);
            }
            shell->i = shell->j;
            shell->end = shell->j;
            while (str[shell->j] && str[shell->j] == ' ')
                shell->j++;
            if (str[shell->j] && (str[shell->j] == '>' || str[shell->j] == '|' || str[shell->j] == '&' || !str[shell->j]))
            {
                while (shell->start < shell->end)
                {
                    str[shell->start] = '\t';///            ls > o -l -s < o -w 
                    shell->start++;
                }
                shell->bol = 0;
                free(shell->stop[0]);
                shell->nbr++;
            }
        }
        else
            shell->i++;
    }
    while (shell->start < shell->end)
    {
        str[shell->start] = '\t';
        shell->start++;
    }
    ft_move_input(shell, str);
    free(shell->stop);
}
