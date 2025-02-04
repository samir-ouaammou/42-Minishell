#include "parsing/Minishell.h"
#include "exaction/exaction.h"

int main(int ac, char **av, char **env)
{
    // t_ast *root = NULL;
    t_parsing shell;
    t_ast *root = NULL;

    if (ac != 1)
    {
        write(2, "Error: Invalid number of arguments.\n", 36);
        exit(-1);
    }
    while (1)
    {
        shell.input = readline("➜ Minishell  ");

        t_data data = {NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        ft_parsing(&shell);
        exaction(shell.three, &data, env);

        add_history(shell.input);
        free(shell.input);
    }
    rl_clear_history();
    return (0);
}