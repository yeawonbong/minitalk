#include "./include/client.h"

static t_client g_client;

void	ft_disconnect(int signo)
{
	ft_putchar_fd('0', STDOUT_FILENO);//
	signo++;
	ft_putstr_fd("\nSent all the signals, Disconnected!\n", STDOUT_FILENO);
	exit(EXIT_SUCCESS);
}

void	ft_send_number(int signo)
{
	ft_putchar_fd('.', STDOUT_FILENO);//
	// printf("GOT_SIGNAL\n");
	// printf("넘버: %d\n", g_client.byte);
	// printf("g_client.byte : %d, %d\n", g_client.byte, g_client.byte & 1);

	// printf("-----------SENT %d\n", g_client.byte & 1);
	signo++; // 이거 빼고 TO_SIGNAL 대체해도 됨 
	ft_putchar_fd('!', STDOUT_FILENO);//
	kill(g_client.spid, (g_client.byte & 1) + TO_SIGNAL); //signo (30)
	g_client.byte = g_client.byte >> 1;
	g_client.count++;
	if (g_client.count < 8)
		return ;
	else if (!g_client.null) //8번째일 때
	{
		if (*(g_client.ptr + 1)) // 다음 byte
		{
			g_client.byte = *(++g_client.ptr);
			g_client.count = 0;
			// printf("-----------------------------char ptr : %c\n", *g_client.ptr);
		}
		else //null 보내려고 
		{
			g_client.byte = 0;
			g_client.null = 1; //얘를 지금 잠시 주석해놨음. 
			// printf("-----------------------------SET_NULL\n");
			g_client.count = 0;
		}
		// if (!g_client.null)
		// printf("종료\n");
		return ;
		// }
		// return ;
	}
	// if (!g_client.null)
	// 	return ;
	printf("loop\n");
	signal(SIGUSR2, &ft_disconnect);
	while(1)
	{}
	// ft_disconnect();
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
		// printf("처음신호 보낸다\n");
	}
	// printf("my pid : %d\n", getpid());
	signal(SIGUSR1, &ft_send_number);
	// signal(SIGUSR2, &ft_disconnect);
	while (1)
	{
	}
	return(0);
}