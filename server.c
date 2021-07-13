#include "minitalk.h"

// void write_char()
// {

// }

void	write_str(int i)
{
	i = 0;
	i++;
	ft_putstr_fd("client pid : ", STDOUT_FILENO);
}

int	main(void)
{
	int	pid;
	// char	*c;
	struct sigaction sig1;
	// struct sigaction sig2;

	sig1.sa_handler = write_str;
	ft_putstr_fd("server pid : ", STDOUT_FILENO);
	ft_putnbr_fd(pid = getpid(), STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	// sigaction(SIGUSR1, &sig1, 0);
	if (sigaction(SIGUSR1, &sig1, 0) == -1)
	{
		printf("signal(SIGUSR1) Error\n");
		return -1;
	}
	while (1)
	{
	}
}

