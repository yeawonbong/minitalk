#include "minitalk.h"

static int	g_currclient;


void	ft_connect(int signo, siginfo_t *siginfo, void *none)
{
	printf("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡINㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");
	printf("---currclient: %d\n---si_pid is : %d\n", g_currclient, siginfo->si_pid);
	if (siginfo->si_pid != g_currclient) //나중에는 8bit 0일때 g_currclient = 0으로 바꿔주고, 0일경우로 조건 넣어주기 (다른 client 차단해야함)
	{
		g_currclient = siginfo->si_pid;
		ft_putstr_fd("Successfully Connected!\n> Client PID : ", STDOUT_FILENO);
		ft_putnbr_fd(siginfo->si_pid, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
	else
	{
		if (signo == SIG1)
		{
			printf("GOT SIGUSR1!\nSIGNO : %d\n", signo);
		}
		else if (signo == SIG2)
			printf("GOT SIGUSR2!\nSIGNO : %d\n", signo);
	}
	kill(siginfo->si_pid, SIGUSR1);
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
	static struct sigaction connect;

	connect.sa_sigaction = ft_connect;
	connect.sa_flags = SA_SIGINFO;
	ft_launch();
	sigaction(SIGUSR1, &connect, NULL);
	sigaction(SIGUSR2, &connect, NULL);
	while (1)
	{
	}
}
