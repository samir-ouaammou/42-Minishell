#include "Minishell.h"

void    ft_free_all(t_parsing *shell)
{
    write(1, "Error\n", 6);
    shell->free = 1337;
    shell->bol = -1;
    if (shell->cmds)
        free(shell->cmds);
    if (shell->cmds_split)
    {
        shell->i = 0;
        while (shell->cmds_split[shell->i])
        {
            free(shell->cmds_split[shell->i]);
            shell->cmds_split[shell->i] = NULL;
            shell->i++;
        }
        free(shell->cmds_split);
        shell->cmds_split = NULL;
    }
}

void    ft_init_parsing(t_parsing *shell)
{
    shell->i = 0;
    shell->j = 0;
    shell->len = 0;
    shell->bol = 0;
    shell->free = 0;
    shell->parentheses = 0;
    shell->cmds = NULL;
    shell->cmds_split = NULL;
}

void    ft_parentheses(t_parsing *shell)
{
    if (shell->free == 1337)
        return ;
    shell->j = 0;
    while (shell->cmds[shell->j])
    {
        if (shell->cmds[shell->j] == '(')
            shell->parentheses++;
        if (shell->cmds[shell->j] == ')')
            shell->parentheses--;
        if (shell->parentheses < 0)
            break ; 
        shell->j++;
    }
    if (shell->parentheses != 0)
        ft_free_all(shell);
}

void    ft_parsing(t_parsing *shell)
{
    ft_init_parsing(shell);
    ft_delete_commits(shell);
    ft_split_args(shell);
    if (shell->free == 1337 || shell->parentheses != 0)
    {
        ft_free_all(shell);
        return ;
    }
    shell->cmds = malloc(shell->len + 1);
    if (!shell->cmds)
        return ;
    shell->len = 0;
    shell->bol = 1337;
    ft_split_args(shell);
    ft_parentheses(shell);
    if (shell->free == 1337)
        return ;
    shell->cmds_split = ft_split(shell->cmds, '\n');


    //******************** */
    shell->i = 0;
    while (shell->cmds_split[shell->i])
    {
        printf("%d ==> %s\n",shell->i, shell->cmds_split[shell->i]);
        shell->i++;
    }
}
















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

        //  ft_execution("tsna");
        
        add_history(shell.input);
        free(shell.input);
        // ft_free_all(&shell);
    }
    rl_clear_history();
    return (0);
}