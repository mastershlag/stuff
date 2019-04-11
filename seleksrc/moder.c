#include "selek.h"

void		ft_controlcer(int signo)
{
	if (signo == SIGINT)
	{
		ft_rebasic(&g_pac, &g_tools);
		ft_termoder(2);
		exit(1);
	}
	if (signo == SIGWINCH)
	{
		ft_rebasic(&g_pac, &g_tools);
		ft_basic(&g_stock, &g_pac, &g_tools);
	}
	if (signo == SIGCONT)
		ft_cannoner();
}

void		ft_termoder(int mode)
{
	static struct termios	orig_tios;

	if (mode == 1)
	{
		if (tcgetattr(STDIN_FILENO, &orig_tios) == -1)
			exit(1);
	}
	else if (mode == 2)
	{
		if (tcsetattr(STDIN_FILENO, TCSANOW, &orig_tios) == -1)
			exit(1);
	}
}

int			ft_cannoner(void)
{
	struct termios	terter;

	if (tcgetattr(STDIN_FILENO, &terter) == -1)
		exit(1);
	ft_termoder(1);
	terter.c_lflag &= ~(ICANON);
	terter.c_lflag &= ~(ECHO);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &terter) == -1)
	{
		ft_termoder(2);
		ft_putstr_fd("Call to tcsetattr() failed\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}
