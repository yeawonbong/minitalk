#include "./include/server.h"

void	ft_send_signal(int client, int signo)
{
	usleep(50);
	kill(client, signo);
}

t_server	ft_init(t_server g_server)
{
	g_server.byte = 0;
	g_server.add = 1; // 2^0
	return (g_server);
}

t_server	ft_connect(int pid, t_server g_server)
{
	g_server.currclient = pid;
	ft_putstr_fd("Successfully Connected!\nClient PID : ", STDOUT_FILENO);
	ft_putnbr_fd(g_server.currclient, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	g_server = ft_init(g_server);
	ft_send_signal(g_server.currclient, SIGUSR1);
	return (g_server);
}

void	ft_server(int signo, siginfo_t *siginfo, void *none)
{
	static t_server g_server;

	none++;
	if (!g_server.currclient) // Client 처음 연결 signal
	{
		g_server = ft_connect(siginfo->si_pid, g_server);
		return ;
	}
	if (siginfo->si_pid != g_server.currclient)
	{
		if (!g_server.nextclient)
			g_server.nextclient = siginfo->si_pid;
		return ;
	}
	g_server.byte += g_server.add * (signo - 30);
	g_server.add *= 2;
	if (g_server.add == 256)
	{
		if (g_server.byte) // NULL이 아니면
		{
			ft_putchar_fd(g_server.byte, STDOUT_FILENO);
			g_server = ft_init(g_server);
		}
		else
		{
			ft_putstr_fd("\nGot all the signals, Disconnected!\n", STDOUT_FILENO);
			ft_send_signal(g_server.currclient, SIGUSR2); // 종료
			if (g_server.nextclient)
			{
				g_server = ft_connect(g_server.nextclient, g_server);
				g_server.nextclient = 0;
			}
			else
				g_server.currclient = 0;
			return ;
		}
	}
	ft_send_signal(g_server.currclient, SIGUSR1);
	return ;
}

int	main(void)
{
	static struct sigaction server;

	server.sa_sigaction = ft_server;
	server.sa_flags = SA_SIGINFO;
	ft_putstr_fd("Server Launched! PID : ", STDOUT_FILENO);
	ft_putnbr_fd(getpid(), STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	while (1)
	{
		sigaction(SIGUSR1, &server, NULL);
		sigaction(SIGUSR2, &server, NULL);
	}
}
