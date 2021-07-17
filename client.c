#include "./include/client.h"

static t_client g_client;

void	ft_disconnect()
{
	ft_putstr_fd("\nSent all the signals, Disconnected!\n", STDOUT_FILENO);
	exit(EXIT_SUCCESS);
}

void	ft_send_number(int signo)
{
	// printf("GOT_SIGNAL\n");
	// printf("넘버: %d\n", g_client.byte);
	// printf("g_client.byte : %d, %d\n", g_client.byte, g_client.byte & 1);

	// printf("-----------SENT %d\n", g_client.byte & 1);
	signo++;
	kill(g_client.spid, (g_client.byte & 1) + TO_SIGNAL);
	usleep(1000);
	g_client.byte = g_client.byte >> 1;
	g_client.count++;
	if (g_client.count < 8)
		return ;
	if (!g_client.null)
	{
		if (*(g_client.ptr + 1))
		{
			g_client.byte = *(++g_client.ptr);
			// printf("-----------------------------char ptr : %c\n", *g_client.ptr);
		}
		else
		{
			g_client.byte = 0;
			g_client.null = 1;
			// printf("-----------------------------SET_NULL\n");
		}
		g_client.count = 0;
		return ;
	}
	ft_disconnect();
}

int main(int argc, char *argv[])
{
	g_client.ptr = argv[2];
	g_client.byte = *g_client.ptr;
	// printf("-----------------------------char ptr : %c\n", *g_client.ptr);

	if (argc != 3)
	{
		ft_putstr_fd("Error : Invalid Input\n", STDOUT_FILENO);
		exit(EXIT_FAILURE);
	}
	if (!g_client.spid)
	{
		g_client.spid = ft_atoi(argv[1]);
		kill(g_client.spid, SIGUSR1); // 처음 연결확인 signal
	}
	// printf("my pid : %d\n", getpid());
	signal(SIGUSR1, &ft_send_number);
	pause();
	while (1)
	{
	}
	return(0);
}