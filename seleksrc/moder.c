#include "selek.h"

void		ft_controlcer(int signo)
{
	if (signo == SIGINT)
	{
		ft_termoder(2);
		exit(1);
	}
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

int			ft_cannoner(t_tcapter *cap)
{
	if (tcgetattr(STDIN_FILENO, &(cap->terter)) == -1)
		exit(1);
	ft_termoder(1);
	cap->terter.c_lflag &= ~(ICANON);
	cap->terter.c_lflag &= ~(ECHO);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &(cap->terter)) == -1)
	{
		ft_termoder(2);
		ft_putstr_fd("Call to tcsetattr() failed\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}
