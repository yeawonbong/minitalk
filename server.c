#include "minitalk.h"

static int	g_currclient;

void	sa_get_sig(int signo, siginfo_t *siginfo, void *none)
{printf("[----IN_GETSIG]\n");
	if (signo == SIG1)
	{
		printf("GOT SIGUSR1!\nSIGNO : %d\n", signo);
	}
	else
		printf("GOT SIGUSR2!\nSIGNO : %d\n", signo);
	kill(siginfo->si_pid, SIGUSR1);

printf("[--EXIT_GETSIG]\n");
	return ;
}

void	sa_connect(int signo, siginfo_t *siginfo, void *hmm)
{
	printf("IN\n");

	int	cpid;

	g_currclient = siginfo->si_pid;
	printf("---currclient: %d\n---Client is : %d\n", g_currclient, siginfo->si_pid);
	// if (g_currclient != siginfo->si_pid)
	// {
	// 	printf("DIFF\n");
	// 	g_currclient = 0;
	// 	return;
	// }
	cpid = siginfo->si_pid;
	static struct sigaction get_sig;
	get_sig.sa_sigaction = sa_get_sig;
	get_sig.sa_flags = SA_SIGINFO;
	ft_putstr_fd("Successfully Connected!\n> Client PID : ", STDOUT_FILENO);
	ft_putnbr_fd(siginfo->si_pid, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	kill(siginfo->si_pid, SIGUSR1);
	// sigaction(SIGUSR1, &get_sig, 0);
	// sigaction(SIGUSR2, &get_sig, 0);
	printf("IN CONNECT SIGNO : %d\n", signo);
	if (sigaction(SIGUSR1, &get_sig, 0) == -1 || sigaction(SIGUSR2, &get_sig, 0) == -1) //어느것이든 일단 들어간다. 
	{
		printf("signal(SIGUSR1) Error\n");
		return ;
	}
	return ;
}

int	main(void)
{
	int	pid;
	static int	currclient =50;
	// char	*c;
	struct sigaction connect; //static? 
	// struct sigaction sig2;

	connect.sa_sigaction = sa_connect;
	connect.sa_flags = SA_SIGINFO;
	ft_putstr_fd("Server Launched! PID : ", STDOUT_FILENO);
	ft_putnbr_fd(pid = getpid(), STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	// sigaction(SIGUSR2, &connect, 0);
	if (sigaction(SIGUSR1, &connect, 0) == -1 || sigaction(SIGUSR2, &connect, 0) == -1) //어느것이든 일단 들어간다. 
	{
		printf("signal(SIGUSR1) Error\n");
		return -1;
	}
	while (1)
	{
	}
}

