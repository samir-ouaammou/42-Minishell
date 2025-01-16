#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "./libft/libft.h"
#include <string.h>

char **split_string(const char *input)
{
    char **args = malloc(10 * sizeof(char *));
    int i = 0;
    int in_quotes = 0;
    char *arg = malloc(100);
    char *ptr = arg;

    while (*input)
    {
        if (*input == '"')
            in_quotes = !in_quotes;
        else if (*input == ' ' && !in_quotes)
        {
            if (ptr != arg) {
                *ptr = '\0';
                args[i++] = strdup(arg);
                ptr = arg;
            }
        } else
            *ptr++ = *input;
        input++;
    }
    if (ptr != arg)
    {
        *ptr = '\0';
        args[i++] = strdup(arg);
    }
    args[i] = NULL;
    free(arg);
    return args;
}

int check_flag_echo(char **str)
{
    int i;
    int j;
    int check;

    if (!str || !str[0] || ft_strncmp(str[0], "echo", ft_strlen("echo")) != 0)
        return (0);
    i = 1;
    check = 0;
    while (str[i] && ft_strncmp(str[i], "-n", ft_strlen("-n")) == 0)
    {
        check = 1;
        i++;
    }
    while (str[i])
    {
        if (ft_strncmp(str[i], "''", ft_strlen("''")) == 0 
            && str[i + 1] && !(str[i + 1][0]))
        {
            check = 0;
            break;
        }
        if (str[i][0] == '\'')
        {
            j = 0;
            while (str[i][j])
            {
                if (str[i][j] != '\'')
                    ft_putchar_fd(str[i][j], 1);
                j++;
            }
        }
        else
            ft_putstr_fd(str[i], 1);
        if (str[i + 1])
            ft_putstr_fd(" ", 1);
        i++;
    }
    if (!check)
        ft_putstr_fd("\n", 1);
    return (1);
}

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    if (!envp)
        return (0);
    char    buffer[1024];
    while (1)
    {
        char *str = readline("\033[0;92m➜\033[0;39m\033[1m\033[96m  Minishell\033[0;39m ");
        char **args = split_string(str);
        int i = 0;
        while (args[i])
        {
            if (ft_strncmp(args[i], "echo", 4) == 0)
                check_flag_echo(args);
            else if (ft_strncmp(args[i], "pwd", 3) == 0)
            {
                if (getcwd(buffer, sizeof(buffer)))
                    ft_printf("%s\n", buffer);
                else
                    perror("pwd error");
            }
            else if (ft_strncmp(args[i], "exit", 4) == 0)
                exit(EXIT_SUCCESS);
            i++;
        }
    }
    exit(EXIT_SUCCESS);
}
