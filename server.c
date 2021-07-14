#include "minitalk.h"

// void write_char()
// {

// }

<<<<<<< HEAD
void	write_str(int signo, siginfo_t *siginfo, void *hmm)
=======
void	write_str(int i, siginfo_t siginfo) //매개변수 int 외에 안받아진다. 일단 save
>>>>>>> b909f9d4b50f259c99cc6b6e15ef0ef5272660b7
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
<<<<<<< HEAD
		// printf("d\n", sig1.sa_flags.si_pid);
=======
>>>>>>> b909f9d4b50f259c99cc6b6e15ef0ef5272660b7
	// ft_putstr_fd(ft_itoa(sig1.sa_flags.si_pid), STDOUT_FILENO);
	while (1)
	{
	}
}

