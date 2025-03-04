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
        return;
    shell->i = 0;
    shell->j = 0;
    shell->nbr = 1;
    shell->help = NULL;
    while (str[shell->i])
    {
        if (str[shell->i] == '\t')
        {
            shell->j++;
            while (str[shell->i] && str[shell->i] == '\t')
                shell->i++;
        }
        if (str[shell->i])
            shell->i++;
    }
    if (shell->j == 0)
        return;
    shell->help = ft_malloc(ft_strlen(str) + (shell->j * 15) + 1);
    if (!shell->help)
        return;
    shell->j = 0;
    shell->i = 0;
    while (str[shell->i])
    {
        if (str[shell->i] == '\t')
        {
            shell->itoa = ft_itoa(shell->nbr);
            shell->name = ft_strjoin("/tmp/heredoc", shell->itoa);
            while (str[shell->i] && str[shell->i] == '\t')
                shell->i++;
            shell->len = 0;
            while (shell->name[shell->len])
            {
                shell->help[shell->j++] = shell->name[shell->len];
                shell->len++;
            }
            shell->nbr++;
        }
        shell->help[shell->j++] = str[shell->i];
        if (str[shell->i])
            shell->i++;
    }
    shell->help[shell->j] = '\0';
    shell->input = ft_strdup(shell->help);
}

void ft_here_doc(t_parsing *shell, char *str, t_exaction *data)
{
    int h;
    int dolar;
    if (!str || !str[0])
        return;
    dolar = 0;
    shell->i = 0;
    shell->bol = 0;
    shell->nbr = 1;
    shell->start = 0;
    shell->end = 0;
    shell->stop = ft_malloc(sizeof(char *) * 2);
    if (!shell->stop)
        return;
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
            while (str[shell->i] && str[shell->i] == ' ')
                shell->i++;
            if (ft_is(str[shell->i]) || !str[shell->i])
            {
                ft_free_args(shell);
                return;
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
                }
            }
            else
            {
                shell->stop[0] = ft_substr(str, shell->i, shell->j - shell->i);
                h = 0;
                while (shell->stop && shell->stop[0] && shell->stop[0][h])
                {
                    if (shell->stop[0][h] == 39)
                    {
                        dolar = 1;
                        break;
                    }
                    h++;
                }
                ft_remove_quots(shell->stop, data, 0);
                shell->itoa = ft_itoa(shell->nbr);
                shell->name = ft_strjoin("/tmp/heredoc", shell->itoa);
                shell->fd = open(shell->name, O_CREAT | O_RDWR | O_TRUNC, 0644);
                while (1)
                {
                    shell->line = readline("heredoc> ");
                    if (!shell->line)
                        break;
                    if (!strcmp(shell->stop[0], shell->line))
                        break;
                    if (!dolar)
                        shell->line = process_strings(shell->line, data);
                    write(shell->fd, shell->line, ft_strlen(shell->line));
                    write(shell->fd, "\n", 1);
                }
                close(shell->fd);
            }
            shell->i = shell->j;
            shell->end = shell->j;
            while (str[shell->j] && str[shell->j] == ' ')
                shell->j++;
            if (str[shell->j] && (str[shell->j] == '>' || str[shell->j] == '|' || str[shell->j] == '&' || !str[shell->j]))
            {
                while (shell->start < shell->end)
                {
                    str[shell->start] = '\t';
                    shell->start++;
                }
                shell->bol = 0;
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
}
