/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahaded <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:15:13 by aahaded           #+#    #+#             */
/*   Updated: 2024/12/09 14:38:32 by aahaded          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

void	setup_pipeline_fork(int argc, char **argv, int i, char **env);
void	check_commands_and_here_doc(int argc, char **argv, char **env);
void	setup_here_doc_input(char **argv);
void	pipe_fork_tcheck_err(pid_t pid, int pipen);
char	*get_path_env(char *cmd, char **env);

#endif
