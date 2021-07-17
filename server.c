#include "./include/server.h"

static t_server g_server;

void	ft_init(void)
{
	g_server.count = 8; // 초기화 함수 짜기, 구조체로 만들기
	g_server.byte = 0;
	g_server.add = 1; // 2^8
}


void	ft_connect(int signo, siginfo_t *siginfo, void *none)
{
	// printf("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡINㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");
	// printf("---currclient: %d\n---si_pid is : %d\n", g_server.currclient, siginfo->si_pid);

	none++;
	if (!g_server.currclient) // Client 처음 연결 signal
	{
 //나중에는 8bit 0일때 g_server.currclient = 0으로 바꿔주고, 0일경우로 조건 넣어주기 (다른 client 차단해야함)
		g_server.currclient = siginfo->si_pid;
		ft_putstr_fd("Successfully Connected!\n> Client PID : ", STDOUT_FILENO);
		ft_putnbr_fd(siginfo->si_pid, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		ft_init();
	}
	else // 여기에 조건 curr_client와 같을때만 넣어주기. 
	{
		g_server.byte += g_server.add * (signo - 30);
		// printf("GOT SIGUSR! -----SIGNO : %d\n", signo - 30);
		// printf("CUR_ADD : %d //// CUR_NUM : %d\n", g_server.add, g_server.byte);
		// printf("BYTE COUNT__%d\n",g_server.count);
		g_server.add *= 2;
		g_server.count--;
	}
	if (g_server.count == 0)
	{
		// printf("문자하나끝남\n");
		if (g_server.byte) // NULL이 아니면
		{
			ft_putchar_fd(g_server.byte, STDOUT_FILENO);
			ft_init();
		}
		else
		{
			g_server.currclient = 0;
			ft_putstr_fd("\nGot all the signals, Disconnected!\n", STDOUT_FILENO);
			// kill(g_server.currclient, SIGUSR2); // Disconnect
			return ;
		}
	}
	// printf("시그널보내\n");
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
	// pause();
	while (1)
	{
	}
}


// 두번째 클라이언트 들어올 때 오류남. 