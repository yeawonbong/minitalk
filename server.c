#include "minitalk.h"

// void write_char()
// {

// }

void	write_str(int signo, siginfo_t *siginfo, void *hmm)
{
	printf("I GOT SIGUSR1!\n");
	ft_putstr_fd("client pid : ", STDOUT_FILENO);
	ft_putnbr_fd(siginfo->si_pid, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	kill(siginfo->si_pid, SIGUSR1);
}

int	main(void)
{
	int	pid;
	// char	*c;
	static struct sigaction mini_connect;
	// struct sigaction sig2;

	sig1.sa_sigaction = write_str;
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
		// printf("d\n", sig1.sa_flags.si_pid);
	// ft_putstr_fd(ft_itoa(sig1.sa_flags.si_pid), STDOUT_FILENO);
	while (1)
	{
	}
}

