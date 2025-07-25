#include "minitalk.h"

void    ft_handler(int  sig)
{
	static int	bit = 0;

	if (sig == SIGUSR1)
	{
		write(1, "0", 1);
	}
	else if (sig == SIGUSR2)
	{
		write(1, "1", 1);
	}
	bit++;
	if (bit % 8 == 0)
		write(1, " ", 1);
}


int main(void)
{
	int srv_pid;

	srv_pid = getpid();
	signal(SIGUSR1, ft_handler);
	signal(SIGUSR2, ft_handler);
	printf("Server PID: %d\n", srv_pid);
	while (1)
		pause();
	return (0);
}
