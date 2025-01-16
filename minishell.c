#include "Parsing/Minishell.h"

int main(int ac, char **av)
{
    t_parsing shell;

    if (ac != 1)
    {
		write (2, "Error: Invalid number of arguments.\n", 36);
        exit(-1);
    }
    while (1)
    {
        shell.input = readline("\033[0;92m➜\033[0;39m\033[1m\033[96m  Minishell\033[0;39m ");

        ft_parsing(&shell);
        ft_execution("tsna");
        
        add_history(shell.input);
        free(shell.input);
    }
    rl_clear_history();
    return (0);
}