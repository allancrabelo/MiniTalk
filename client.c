#include "minitalk.h"

int	ft_atoi(char *str)
{
	int	sign;
	int	result;
	int	i;

	sign = 1;
	result = 0;
	i = 0;
	while(str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (sign * result);
}

int	send_message(char *msg, pid_t pid)
{
	int	i;
	int	j;

	i = 0;
	while (msg[i])
	{
		j = 7;
		while (j >= 0)
		{
			if (msg[i] & (1 << j))
			{
				if (kill(pid, SIGUSR2) == -1)
					return (2);
			}
			else if (kill(pid, SIGUSR1) == -1)
				return (1);
			j--;
			usleep(100);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	pid_t	srv_pid;

	if (argc != 3)
		return (write(1, "Usage ./client <PID> <STRING>\n", 30));
	srv_pid = atoi(argv[1]);
	send_message(argv[2], srv_pid);
	return (0);
}