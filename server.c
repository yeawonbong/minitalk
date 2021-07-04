#include "minitalk.h"

int	main(void)
{
	int	pid;

	ft_putstr_fd("server pid : ", STDOUT_FILENO);
	ft_putnbr_fd(pid = getpid(), STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	while (1)
	{
	}
}
