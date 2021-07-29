#include "./include/minitalk.h"

void	ft_send_signal(int pid, int signo)
{
	usleep(50);
	kill(pid, signo);
}
