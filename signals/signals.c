#include "../minishell.h"

struct s_exaction	*data_struc(void)
{
	static struct s_exaction	data_struc = {0};

	return (&data_struc);
}

void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		ft_exit(130);
	}
}

void	handle_signal(int sig)
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
