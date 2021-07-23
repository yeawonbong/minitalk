#include "./include/server.h"

static int	g_currclient; // 전역 구조체 변수로 만들기
static int	g_count;
static int	g_byte;
static int	g_add;

void	ft_init(void)
{
	g_count = 8; // 초기화 함수 짜기, 구조체로 만들기
	g_byte = 0;
	g_add = 1; // 2^8
}


void	ft_connect(int signo, siginfo_t *siginfo, void *none)
{
	// ft_putchar_fd('.', STDOUT_FILENO);//
	none++;
	if (!g_currclient) // Client 처음 연결 signal
	{
 //나중에는 8bit 0일때 g_currclient = 0으로 바꿔주고, 0일경우로 조건 넣어주기 (다른 client 차단해야함)
		g_currclient = siginfo->si_pid;
		ft_putstr_fd("Successfully Connected!\n Client PID : ", STDOUT_FILENO);
		ft_putnbr_fd(siginfo->si_pid, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		ft_init();
		// usleep(50);
		// kill(g_currclient, SIGUSR1);
		// return ;
	}
	else if (siginfo->si_pid == g_currclient)
	{
		g_byte += g_add * (signo - 30);
		g_add *= 2;
		g_count--;
	// }
		if (g_count == 0)
		{
			// ft_putstr_fd("문자하나끝남\n", STDOUT_FILENO);
			if (g_byte) // NULL이 아니면
			{
				// ft_putstr_fd("----------------------", STDOUT_FILENO);
				ft_putchar_fd(g_byte, STDOUT_FILENO);
				// printf("\n");
				ft_init();
				// kill(siginfo->si_pid, SIGUSR1);
				// return ;
			}
			else
			{
				ft_putstr_fd("\nGot all the signals, Disconnected!\n", STDOUT_FILENO);
				g_currclient = 0;
				usleep(50);
				kill(siginfo->si_pid, SIGUSR2); // Disconnect
				ft_init();
				return ;
			}
		}
	}
	// ft_putstr_fd("시그널보낸다\n", STDOUT_FILENO);
	usleep(50);
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
	while (1)
	{
		sigaction(SIGUSR1, &connect, NULL);
		sigaction(SIGUSR2, &connect, NULL);
	}
}
