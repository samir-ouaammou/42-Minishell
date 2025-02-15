#include "../minishell.h"

void	ft_skip_quots(t_parsing *shell)
{
	shell->chr = shell->input[shell->i];
	while (shell->input[shell->i])
	{
		shell->i++;
		if ((shell->input[shell->i]) && (shell->input[shell->i] == shell->chr))
			break ;
	}
	shell->i++;
}

int	ft_is_symbol_(t_parsing *shell)
{
	if (!shell->input || !shell->input[shell->i])
		return (0);
	if (shell->input[shell->i] != '|'
        && shell->input[shell->i] != '('
        && shell->input[shell->i] != ')'
        && shell->input[shell->i] != '<'
        && shell->input[shell->i] != '>'
        && shell->input[shell->i] != '&')
		return (1);
	return (0);
}

void    ft_echo_str(t_parsing *shell)
{
    shell->i = 0;
    while (shell->input[shell->i])
    {
        // if ((shell->input[shell->i] == '"' || shell->input[shell->i] == '\'') && shell->input[shell->i + 1])
        //     ft_skip_quots(shell);

        if (shell->input[shell->i] == ';' || shell->input[shell->i] == '\n')
            break;
        while (!ft_is_symbol_(shell))
            shell->i++;

        if (strncmp(&shell->input[shell->i], "echo", 4) == 0 || strncmp(&shell->input[shell->i], "echo4", 4) == 0)
        {
            printf("echo ");
            shell->i += 5;
            while (shell->input[shell->i] == ' ' || shell->input[shell->i] == '\t')
                shell->i++;

            while (shell->input[shell->i] && shell->input[shell->i] != '\n' && shell->input[shell->i] != ';' && ft_is_symbol_(shell))
            {
                if (shell->input[shell->i] == '"' || shell->input[shell->i] == '\'')
                {
                    shell->chr = shell->input[shell->i];
                    while (shell->input[shell->i])
                    {
                        printf("%c", shell->input[shell->i]);
                        shell->i++;
                        if ((shell->input[shell->i]) && (shell->input[shell->i] == shell->chr))
                            break ;
                    }
                }
                printf("%c", shell->input[shell->i]);
                shell->i++;
            }
            printf("\n");
            // return;
        }
        if (shell->input[shell->i])
            shell->i++;
    }
}

//      "123"   echo "hh|hh"    

