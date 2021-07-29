#include "./include/minitalk.h"

void	ft_send_signal(int pid, int signo)
{
	usleep(50);
	kill(pid, signo);
}

t_server	ft_init(t_server server)
{
	server.byte = 0;
	server.add = 1; // 2^0
	return (server);
}

t_server	ft_connect(int pid, t_server server)
{
	server.currclient = pid;
	ft_putstr_fd("Successfully Connected!\nClient PID : ", STDOUT_FILENO);
	ft_putnbr_fd(server.currclient, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	server = ft_init(server);
	ft_send_signal(server.currclient, SIGUSR1);
	return (server);
}

void	ft_server(int signo, siginfo_t *siginfo, void *none)
{
	static t_server server;

	none++;
	if (!server.currclient) // Client 처음 연결 signal
	{
		server = ft_connect(siginfo->si_pid, server);
		return ;
	}
	if (siginfo->si_pid != server.currclient)
	{
		if (!server.nextclient)
			server.nextclient = siginfo->si_pid;
		return ;
	}
	server.byte += server.add * (signo - 30);
	server.add *= 2;
	if (server.add == 256)
	{
		if (server.byte) // NULL이 아니면
		{
			ft_putchar_fd(server.byte, STDOUT_FILENO);
			server = ft_init(server);
		}
		else
		{
			ft_putstr_fd("\nGot all the signals, Disconnected!\n", STDOUT_FILENO);
			ft_send_signal(server.currclient, SIGUSR2); // 종료
			if (server.nextclient)
			{
				server = ft_connect(server.nextclient, server);
				server.nextclient = 0;
			}
			else
				server.currclient = 0;
			return ;
		}
	}
	ft_send_signal(server.currclient, SIGUSR1);
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
