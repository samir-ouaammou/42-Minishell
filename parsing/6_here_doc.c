#include "../minishell.h"

int ft_is(char c)
{
    if (c == '<' || c == '>' || c == '|' || c == '&' || c == ' ' || c == '\t')
        return (1);
    return (0);
}

void ft_here_doc(t_parsing *shell)
{
    char *delimiter;
    char *line;
    int start;
    char quote;
    int j;

    if (!shell || !shell->input)
        return;

    shell->i = 0;
    while (shell->input[shell->i])
    {
        if (shell->input[shell->i] == '"' || shell->input[shell->i] == '\'')
        {
            quote = shell->input[shell->i];
            start = shell->i;
            shell->i++;
            while (shell->input[shell->i] && shell->input[shell->i] != quote)
                shell->i++;
            if (shell->input[shell->i] == '\0')
                return;
            shell->i++;
        }

        if (shell->input[shell->i] == '<' && shell->input[shell->i + 1] == '<')
        {
            shell->i += 2;
            j = shell->i;

            while (shell->input[shell->i] == ' ' || shell->input[shell->i] == '\t')
                shell->i++;

            if (shell->input[shell->i] == '<')
            {
                write(1, "error\n", 6);
                return;
            }

            if (shell->input[shell->i] == '\0')
                return;

            if (shell->input[shell->i] == '"' || shell->input[shell->i] == '\'')
            {
                quote = shell->input[shell->i];
                start = shell->i;
                shell->i++;
                while (shell->input[shell->i] && shell->input[shell->i] != quote)
                    shell->i++;

                if (shell->input[shell->i] == '\0')
                {
                    while (1)
                    {
                        line = readline("here_doc> ");
                        if (!line)
                            break;
                        free(line);
                    }
                    write(1, "\n", 1);
                    return;
                }
                shell->i++;
            }
            else
            {
                start = shell->i;
                while (shell->input[shell->i] && shell->input[shell->i] != '\n' && shell->input[shell->i] != '"' && shell->input[shell->i] != '\'' && !ft_is(shell->input[shell->i]))
                    shell->i++;
            }

            if (shell->input[shell->i] == '\n')
            {
                write(1, "error\n", 6);
                return;
            }

            if (start != shell->i)
            {
                delimiter = strndup(shell->input + start, shell->i - start);
                if (!delimiter)
                    return;

                while (1)
                {
                    line = readline("here_doc> ");
                    if (!line)
                        break;
                    if (line[strlen(line) - 1] == '\n')
                        line[strlen(line) - 1] = '\0';
                    if (strcmp(line, delimiter) == 0)
                    {
                        free(line);
                        break;
                    }
                    free(line);
                }
                free(delimiter);
            }
        }
        else
        {
            shell->i++;
        }
    }
}

