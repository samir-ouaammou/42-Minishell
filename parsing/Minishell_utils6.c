// #include "Minishell.h"
// #include "../libft/libft.h"

// // void    ft_delete_commits(t_parsing *shell)
// // {
// //     if (!shell->input || !shell->input[0])
// //         return ;
// //     shell->i = 0;
// //     while (shell->input[shell->i])
// //     {
// //         if (shell->input[shell->i] == '#')
// //             break ;
// //         shell->i++;
// //     }
// //     if (shell->input[shell->i] == '#')
// //     {
// //         while (shell->input[shell->i])
// //         {
// //             shell->input[shell->i] = ' ';
// //             shell->i++;
// //         }
// //     }
// // }

// // void    ft_check_single(t_parsing *shell, int bol)
// // {
// //     if (bol == 1)
// //     {
// //         if (shell->bol == 0)
// //             shell->len += 3;
// //         else
// //         {
// //             shell->cmds[shell->len++] = '\n';
// //             shell->cmds[shell->len++] = shell->input[shell->i];
// //             shell->cmds[shell->len++] = '\n';
// //         }
// //     }
// //     else
// //     {
// //         if (shell->bol == 0)
// //             shell->len += 1;
// //         else
// //         {
// //             if (shell->input[shell->i] == ' ')
// //                 shell->cmds[shell->len++] = '\n';
// //             else
// //                 shell->cmds[shell->len++] = shell->input[shell->i];
// //         }
// //     }
// // }

// // void    ft_check_double(t_parsing *shell)
// // {
// //     if (shell->input[shell->i] == shell->input[shell->i + 2])
// //     {
// //         ft_free_all(shell);
// //         return ;
// //     }
// //     if (shell->bol == 0)
// //         shell->len += 4;
// //     else
// //     {
// //         shell->cmds[shell->len++] = '\n';
// //         shell->cmds[shell->len++] = shell->input[shell->i];
// //         shell->cmds[shell->len++] = shell->input[shell->i++];
// //         shell->cmds[shell->len++] = '\n';
// //     }
// // }

// // void    ft_skip_string(t_parsing *shell)
// // {
// //     shell->chr = shell->input[shell->i];
// //     while (shell->input[shell->i])
// //     {
// //         if (shell->bol == 0)
// //             ft_check_single(shell, 0);
// //         else
// //             shell->cmds[shell->len++] = shell->input[shell->i];
// //         shell->i++;
// //         if (shell->input[shell->i] == shell->chr)
// //         {
// //             if (shell->bol == 0)
// //                 ft_check_single(shell, 0);
// //             else
// //                 shell->cmds[shell->len++] = shell->input[shell->i];
// //             return ;
// //         }
// //     }
// //     ft_free_all(shell);
// // }

// // void    ft_check_syntax_errors(t_parsing *shell)
// // {
// //     shell->i = 0;
// //     while (shell->input[shell->i])
// //     {
// //         if (shell->input[shell->i] == 34 || shell->input[shell->i] == 39)
// //             ft_skip_string(shell);
// //         else if ((shell->input[shell->i] == '|' && shell->input[shell->i
		+ 1] == '|')
// //             || (shell->input[shell->i] == '&' && shell->input[shell->i
	+ 1] == '&')
// //             || (shell->input[shell->i] == '>' && shell->input[shell->i
	+ 1] == '>')
// //             || (shell->input[shell->i] == '<' && shell->input[shell->i
	+ 1] == '<'))
// //             ft_check_double(shell);
// //         else if (shell->input[shell->i] == '|'
	|| shell->input[shell->i] == '<'
// //             || shell->input[shell->i] == '>'
	|| shell->input[shell->i] == '('
// //             || shell->input[shell->i] == ')'
	|| shell->input[shell->i] == '='
// //             || shell->input[shell->i] == ':')
// //             ft_check_single(shell, 1);
// //         else
// //             ft_check_single(shell, 0);
// //         if(shell->input[shell->i])
// //             shell->i++;
// //         if (shell->free == 1337)
// //             return ;
// //     }
// //     if (shell->bol != 0)
// //         shell->cmds[shell->len] = '\0';
// // }
