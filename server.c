#include "minitalk.h"

static int	g_currclient;

void	ft_get_sig(int signo, siginfo_t *siginfo, void *none)
{printf("[----IN_GETSIG]\n");
	if (signo == SIG1)
	{
		printf("GOT SIGUSR1!\nSIGNO : %d\n", signo);
	}
	else if (signo == SIG2)
		printf("GOT SIGUSR2!\nSIGNO : %d\n", signo);
	// kill(siginfo->si_pid, SIGUSR1);

printf("[--EXIT_GETSIG]\n");
	return ;
}

void	ft_connect(int signo, siginfo_t *siginfo, void *none)
{
	printf("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡINㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");

	printf("!!!!!!!!!si_pid : %d\n", siginfo->si_pid);
	if (!g_currclient)
	{
		g_currclient = siginfo->si_pid;
	}
	printf("---currclient: %d\n---Client is : %d\n", g_currclient, siginfo->si_pid);
	// if (g_currclient != siginfo->si_pid)
	// {
	// 	printf("DIFF\n");
	// 	g_currclient = 0;
	// 	return;
	// }
	// static struct sigaction get_sig;
	// get_sig.sa_sigaction = ft_get_sig;
	// get_sig.sa_flags = SA_SIGINFO;
	if (siginfo->si_pid != g_currclient)
	{
		ft_putstr_fd("Successfully Connected!\n> Client PID : ", STDOUT_FILENO);
		ft_putnbr_fd(siginfo->si_pid, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
	ft_get_sig(signo, siginfo, none);
	// kill(siginfo->si_pid, SIGUSR1);
	// sigaction(SIGUSR1, &get_sig, 0);
	// sigaction(SIGUSR2, &get_sig, 0);
	printf("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡOUT : %dㅡㅡㅡㅡㅡㅡ\n", signo);
	// pause();
	// if (sigaction(SIGUSR1, &get_sig, 0) == -1 || sigaction(SIGUSR2, &get_sig, 0) == -1) //어느것이든 일단 들어간다. 
	// {
	// 	printf("signal(SIGUSR1) Error\n");
	// 	return ;
	// }
	return ;
}

void	ft_launch()
{
	ft_putstr_fd("Server Launched! PID : ", STDOUT_FILENO);
	ft_putnbr_fd(getpid(), STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
}

int	main(void)
{
	// static int	currclient =50;
	// char	*c;
	struct sigaction connect; //static? 
	// struct sigaction sig2;

	connect.sa_sigaction = ft_connect;
	connect.sa_flags = SA_SIGINFO;
	ft_launch();
	sigaction(SIGUSR1, &connect, 0);
	sigaction(SIGUSR2, &connect, 0);
	// if (sigaction(SIGUSR1, &connect, 0) == -1 || sigaction(SIGUSR2, &connect, 0) == -1) //어느것이든 일단 들어간다. 
	// {
	// 	printf("signal(SIGUSR1) Error\n");
	// 	return -1;
	// }
	while (1)
	{
	}
}

