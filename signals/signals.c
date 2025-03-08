#include "../minishell.h"

struct s_exaction *data_struc()
{
	static struct s_exaction data_struc = {0};
	return &data_struc;
}

void sigint_handler(int sig)
{
    if (sig == SIGINT)
    {
        write(1, "\n", 1);
        ft_exit(130);
    }
}

int	handle_child_exit_status(int status)
{
	int	fd;

	fd = 0;
	if (WIFEXITED(status))
	{
		fd = WEXITSTATUS(status);
		if (fd == 130)
		{
			data_struc()->exit_status = 130;
			data_struc()->bol = 1;
			return (1);
		}
	}
	return (0);
}

void handle_signal(int sig)
{
	(void)sig;
	if (data_struc()->is_foreground == 1)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		data_struc()->exit_status = 130;
	}
}

int	handle_forked_process(t_parsing *shell, int dolar, t_exaction *data)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		return (1);
	}
	else if (pid == 0)
	{
		signal(SIGINT, sigint_handler);
		ft_read_and_process_heredoc_input(shell, dolar, data);
		close(shell->fd);
		ft_exit(0);
	}
	waitpid(pid, &status, 0);
	return (handle_child_exit_status(status));
}
