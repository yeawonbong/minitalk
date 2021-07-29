#include "./include/client.h"

static char *g_ptr;

void	ft_send_signal(int pid, int signo)
{
	usleep(50);
	kill(pid, signo);
}

void	ft_disconnect(int signo)
{
	signo++;
	ft_putstr_fd("Sent all the signals, Disconnected!\n", STDOUT_FILENO);
	exit(EXIT_SUCCESS);
}

void	ft_send_number(int signo, siginfo_t *siginfo, void *none)
{
	static t_client	client;

	none++;
	ft_send_signal(siginfo->si_pid, (*g_ptr & 1) + signo); //signo (30)
	*g_ptr = *g_ptr >> 1;
	client.count++;
	if (client.count < 8)
		return ;
	if (!client.null) //8번째일 때
	{
		if (*(g_ptr + 1)) // 다음 byte
			g_ptr++;
		else //null 보내려고 
			client.null = 1;
		client.count = 0;
	}
	while (client.null && client.count == 8)
		signal(SIGUSR2, &ft_disconnect);
	return ;
}

int main(int argc, char *argv[])
{
	static struct sigaction client;

	client.sa_sigaction = ft_send_number;
	client.sa_flags = SA_SIGINFO;
	g_ptr = argv[2];
	if (argc != 3)
	{
		ft_putstr_fd("Error : Invalid Input\n", STDOUT_FILENO);
		exit(EXIT_FAILURE);
	}
	ft_send_signal(ft_atoi(argv[1]), SIGUSR1);
	while (1)
		sigaction(SIGUSR1, &client, NULL);
	return(0);
}
