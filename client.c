#include "minitalk.h"

static int	g_spid;
static int	g_num;

void	send_end(int spid)
{
	int i;

	i = 8;
	while (i--)
		kill(spid, SIGUSR1);
}

void	ft_send_number(int signo)
{
	while(g_num)
	{
		printf("g_num : %d, %d\n", g_num, g_num & 1);
		if (g_num & 1)
		{
			kill(g_spid, SIGUSR2);
			printf("SENT 1\n");
		}
		else if ((g_num & 1) == 0)
		{
			kill(g_spid, SIGUSR1);
			printf("SETNT 0\n");
		}
		g_num = g_num >> 1;
		printf("나간다\n");
		return ;
	}
	exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
	struct sigaction sig1;
	g_num = 10;
	printf("first g_num : %d\n", g_num);
	if (argc != 3)
		exit(EXIT_FAILURE);
	if (!g_spid)
	{
		g_spid = ft_atoi(argv[1]);
		kill(g_spid, SIGUSR1);
	}
	printf("my pid : %d\n", getpid());
	signal(SIGUSR1, &ft_send_number);
	printf("넘버: %d\n", g_num);
	while(g_num)
	{}
	return(0);
}