#include "./include/server.h"

static t_server g_server;

void	ft_launch()
{
	ft_putstr_fd("Server Launched! PID : ", STDOUT_FILENO);
	ft_putnbr_fd(getpid(), STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
}

void	ft_init(void)
{
	g_server.count = 8;
	g_server.byte = 0;
	g_server.add = 1; // 2^0
}

void	ft_connect(int pid)
{
	g_server.currclient = pid;
	ft_putstr_fd("Successfully Connected!\nClient PID : ", STDOUT_FILENO);
	ft_putnbr_fd(g_server.currclient, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	ft_init();
	usleep(50);
	kill(g_server.currclient, SIGUSR1);
}


void	ft_server(int signo, siginfo_t *siginfo, void *none)
{
	none++;
	if (!g_server.currclient) // Client 처음 연결 signal
	{
		ft_connect(siginfo->si_pid);
		// g_server.currclient = siginfo->si_pid;
		// ft_putstr_fd("Successfully Connected!\nClient PID : ", STDOUT_FILENO);
		// ft_putnbr_fd(siginfo->si_pid, STDOUT_FILENO);
		// ft_putchar_fd('\n', STDOUT_FILENO);
		// ft_init();
		// usleep(50);
		// kill(g_server.currclient, SIGUSR1);
		return ;
	}
	if (siginfo->si_pid != g_server.currclient)
	{
		g_server.nextclient = siginfo->si_pid;
		return ;
	}
	g_server.byte += g_server.add * (signo - 30);
	g_server.add *= 2;
	g_server.count--;
	if (g_server.count == 0)
	{
		if (g_server.byte) // NULL이 아니면
		{
			ft_putchar_fd(g_server.byte, STDOUT_FILENO);
			ft_init();
		}
		else
		{
			ft_putstr_fd("\nGot all the signals, Disconnected!\n", STDOUT_FILENO);
			usleep(50);
			kill(siginfo->si_pid, SIGUSR2); // Disconnect
			if (g_server.nextclient)
			{
				ft_connect(g_server.nextclient);
				g_server.nextclient = 0;
			}
			else
				g_server.currclient = 0;
			ft_init();
			return ;
		}
	}
	usleep(50);
	kill(siginfo->si_pid, SIGUSR1);
	return ;
}

int	main(void)
{
	static struct sigaction server;

	server.sa_sigaction = ft_server;
	server.sa_flags = SA_SIGINFO;
	ft_launch();
	while (1)
	{
		sigaction(SIGUSR1, &server, NULL);
		sigaction(SIGUSR2, &server, NULL);
	}
}
