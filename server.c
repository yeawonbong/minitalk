#include "minitalk.h"

// void write_char()
// {

// }

void	write_str(int i, siginfo_t siginfo) //매개변수 int 외에 안받아진다. 일단 save
{
	printf("I GOT SIGUSR1! \n");
	i = 0;
	i++;
	ft_putstr_fd("client pid : ", STDOUT_FILENO);
}

int	main(void)
{
	int	pid;
	// char	*c;
	static struct sigaction sig1;
	// struct sigaction sig2;

	sig1.sa_handler = write_str;
	sig1.sa_flags = SA_SIGINFO;
	ft_putstr_fd("server pid : ", STDOUT_FILENO);
	ft_putnbr_fd(pid = getpid(), STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	// sigaction(SIGUSR1, &sig1, 0);
	if (sigaction(SIGUSR1, &sig1, 0) == -1)
	{
		printf("signal(SIGUSR1) Error\n");
		return -1;
	}
	else
	// ft_putstr_fd(ft_itoa(sig1.sa_flags.si_pid), STDOUT_FILENO);
	while (1)
	{
	}
}

