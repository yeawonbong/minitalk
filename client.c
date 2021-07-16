#include "minitalk.h"

void	send_end(int spid)
{
	int i;

	i = 8;
	while (i--)
		kill(spid, SIGUSR1);
}

void	send_sig1(int signo, siginfo_t *siginfo, void *none)
{
	printf("GOT SIG__send1\n");
	kill(siginfo->si_pid, SIGUSR1);
}

void	send_sig2(int signo, siginfo_t *siginfo, void *none)
{
	printf("GOT SIG__send2\n");
	kill(siginfo->si_pid, SIGUSR2);
}


void	ft_send_number(int spid)
{
	int	num;
	int	len;

	num = 10;
	//2 len = 1;
	// while (temp && (temp /= 10))
	// 	len++;
	// printf("len is %d\n", len);
	while(num)
	{
		printf("num : %d, %d\n", num, num & 1);
		if (num & 1)
		{
			// sigaction(SIGUSR1, &sig2, 0);
			kill(spid, SIGUSR2);
			printf("SENT 1\n");
		}
		else if ((num & 1) == 0)
		{
			// sigaction(SIGUSR1, &sig1, 0);
			kill(spid, SIGUSR1);
			printf("SETNT 0\n");
		}
		num = num >> 1;
	}
	return ;
}


void	send_number(int signo, siginfo_t *siginfo, void *none)
{
	ft_send_number(siginfo->si_pid);
	// int	num;
	// int	len;
	// struct sigaction sig1;
	// struct sigaction sig2;


	// num = 10;
	// //2 len = 1;
	// // while (temp && (temp /= 10))
	// // 	len++;
	// // printf("len is %d\n", len);
	// sig1.sa_sigaction = send_sig1;
	// sig2.sa_sigaction = send_sig2;
	// sig1.sa_flags = SA_SIGINFO;
	// sig2.sa_flags = SA_SIGINFO;
	// while(num)
	// {
	// 	printf("num : %d\n", num);
	// 	pause();
	// 	if (num & 1)
	// 	{
	// 		// sigaction(SIGUSR1, &sig2, 0);
	// 		kill(siginfo->si_pid, SIGUSR2);
	// 		printf("SENT 1\n");
	// 	}
	// 	else
	// 	{
	// 		// sigaction(SIGUSR1, &sig1, 0);
	// 		kill(siginfo->si_pid, SIGUSR1);
	// 		printf("SETNT 0\n");
	// 	}
	// 	num = num >> 1;
	// }
}

int main(int argc, char *argv[])
{
	int spid;
	int cpid;
	struct sigaction sig1;

	sig1.sa_sigaction = send_number;
	sig1.sa_flags = SA_SIGINFO;
	if (argc != 3)
		exit(EXIT_FAILURE);
	spid = ft_atoi(argv[1]);
	cpid = getpid();
	// kill(spid, SIGUSR1);
	printf("my pid : %d\n", cpid);
	// pause();
	// sigaction(SIGUSR1, &sig1, 0);
	ft_send_number(spid);
	// while(1)
	// {}
	return(0);
}