#include "./include/client.h"

static t_client g_client;

void	ft_disconnect(int signo)
{
	signo++;
	ft_putstr_fd("Sent all the signals, Disconnected!\n", STDOUT_FILENO);
	exit(EXIT_SUCCESS);
}

void	ft_send_number(int signo)
{
<<<<<<< HEAD
	usleep(50);
=======
	usleep(100);
>>>>>>> deleting_comments_process
	kill(g_client.spid, (g_client.byte & 1) + signo); //signo (30)
	g_client.byte = g_client.byte >> 1;
	g_client.count++;
	if (g_client.count < 8)
		return ;
	if (!g_client.null) //8번째일 때
	{
		if (*(g_client.ptr + 1)) // 다음 byte
			g_client.byte = *(++g_client.ptr);
		else //null 보내려고 
		{
			g_client.byte = 0;
<<<<<<< HEAD
			g_client.null = 1; //얘를 지금 잠시 주석해놨음.
		}
	}
	// printf("ENDS\n");
	// i = 8;
	// while(0 < i--)
	// {
	// 	kill(spid, SIGUSR1);
	// 	usleep(1000);
	// 	// printf("SNED NULL\n");
	// }
	while(1)
		signal(SIGUSR2, &ft_disconnect);
=======
			g_client.null = 1;
			g_client.count = 0;
		}
	}
	return ;
>>>>>>> deleting_comments_process
}

int main(int argc, char *argv[])
{
	g_client.ptr = argv[2];
	g_client.byte = *g_client.ptr;
	if (argc != 3)
	{
		ft_putstr_fd("Error : Invalid Input\n", STDOUT_FILENO);
		exit(EXIT_FAILURE);
	}
	if (!g_client.spid)
	{
		g_client.spid = ft_atoi(argv[1]);
		usleep(50);
		kill(g_client.spid, SIGUSR1); // 처음 연결확인 signal
	}
<<<<<<< HEAD
=======
	signal(SIGUSR1, &ft_send_number);
	signal(SIGUSR2, &ft_disconnect);
>>>>>>> deleting_comments_process
	while (1)
	{
		signal(SIGUSR1, &ft_send_number);
		signal(SIGUSR2, &ft_disconnect);
	}
	return(0);
}